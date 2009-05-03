#include "server_impl.hpp"
#include "is_disconnect.hpp"
#include "io_service_wrapper.hpp"
#include "connection.hpp"
#include "../log.hpp"
#include "../exception.hpp"
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <sge/lexical_cast.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/foreach.hpp>
#include <iostream>

sanguis::net::detail::server_impl::server_impl()
:
	io_service_(
		detail::io_service_wrapper()
	),
	acceptor_(
		io_service_
	),
	id_counter_(
		static_cast<id_type>(0)),
	handlers_(0)
{}

void sanguis::net::detail::server_impl::listen(
	port_type const port)
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("server: listening on port ")
		             << port);

	boost::asio::ip::tcp::endpoint endpoint(
		boost::asio::ip::tcp::v4(),
		port);
	acceptor_.open(
		endpoint.protocol());
	acceptor_.set_option(
		boost::asio::ip::tcp::acceptor::reuse_address(
			true));
	acceptor_.bind(
		endpoint);
	acceptor_.listen();

	accept();
}

void sanguis::net::detail::server_impl::process()
{
	BOOST_FOREACH(connection_container::reference c,connections_)
	{
		if (c.sending_ || !c.output_.characters_left())
			continue;

		c.sending_ = true;

		data_type const &out_data(
			c.output_.buffer()
		);

		c.socket_.async_send(
			boost::asio::buffer(
				out_data.data(),
				out_data.size()
			),
			boost::bind(
				&server_impl::write_handler,
				this,
				_1,
				_2,
				boost::ref(c)));
		handlers_++;
	}

	if (handlers_)
	{
		boost::system::error_code e;
		io_service_.poll(e);
		if (e)
			throw exception(
				SGE_TEXT("poll error: ")+
				sge::iconv(
					e.message()));
	}
}

void sanguis::net::detail::server_impl::queue(
	data_type const &s)
{
	BOOST_FOREACH(connection_container::reference c,connections_)
	{
		if (!c.connected_)
			continue;
		c.output_.push_back(
			s);
	}
}

void sanguis::net::detail::server_impl::queue(
	id_type const id,
	data_type const &s)
{
	BOOST_FOREACH(connection_container::reference c,connections_)
	{
		if (c.id_ != id)
			continue;

		if (!c.connected_)
			throw exception(
				SGE_TEXT("invalid id ")+
				sge::lexical_cast<sge::string>(
					id));

		c.output_.push_back(
			s);

		return;
	}

	// no valid id found?
	throw exception(
		SGE_TEXT("invalid id ")+
		sge::lexical_cast<sge::string>(
			id));
}

sge::signal::auto_connection sanguis::net::detail::server_impl::register_connect(
	server::connect_function const &f)
{
	return connect_signal_.connect(
		f);
}

sge::signal::auto_connection sanguis::net::detail::server_impl::register_disconnect(
	server::disconnect_function const &f)
{
	return disconnect_signal_.connect(
		f);
}

sge::signal::auto_connection sanguis::net::detail::server_impl::register_data(
	server::data_function const &f)
{
	return data_signal_.connect(
		f);
}

void sanguis::net::detail::server_impl::accept()
{
	connections_.push_back(
		new connection(
			id_counter_++,
			io_service_));

	connection &c = connections_.back();

	acceptor_.async_accept(
		c.socket_,
		boost::bind(
			&server_impl::accept_handler,
			this,
			_1,
			boost::ref(c)));

	handlers_++;
}

void sanguis::net::detail::server_impl::read_handler(
	boost::system::error_code const &e,
	std::size_t const bytes,
	connection &c)
{
	handlers_--;

	if (e)
	{
		handle_error(SGE_TEXT("server read"),e,c);
		return;
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("server: reading ")
			<< bytes 
			<< SGE_TEXT(" bytes."));
	
	data_signal_(
		c.id_,
		data_type(
			c.new_data_.begin(),
			c.new_data_.begin() + bytes));

	// receive some more
	c.socket_.async_receive(
		boost::asio::buffer(
			c.new_data_),
		boost::bind(
			&server_impl::read_handler,
			this,
			_1,
			_2,
			boost::ref(
				c)));
	handlers_++;
}

void sanguis::net::detail::server_impl::write_handler(
	boost::system::error_code const &e,
	std::size_t const bytes,
	connection &c)
{
	handlers_--;

	if (e)
	{
		handle_error(
			SGE_TEXT("server write"),
			e,
			c);
		return;
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("server: wrote ")
			<< bytes 
			<< SGE_TEXT(" bytes.")
	);

	c.output_.erase(
		bytes);

	// are there bytes left to send?
	if (!c.output_.characters_left())
	{
		c.sending_ = false;
		return;
	}

	data_type const &data(
		c.output_.buffer()
	);

	c.socket_.async_send(
		boost::asio::buffer(
			data.data(),
			data.size()
		),
		boost::bind(
			&server_impl::write_handler,
			this,
			_1,
			_2,
			boost::ref(c)
		)
	);

	handlers_++;
}

void sanguis::net::detail::server_impl::accept_handler(
	boost::system::error_code const &e,
	connection &c)
{
	handlers_--;

	if (e)
	{
		SGE_LOG_DEBUG(
			log(),
			sge::log::_1 << SGE_TEXT("server: error while accepting"));
		throw exception(
			sge::iconv(
				e.message()));
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("server: accepting a connection"));

	// first set connected, _then_ call handler 
	// (else queueing code in the handler can't work)
	c.connected_ = true;

	// send signal to handlers
	connect_signal_(
		c.id_);

	c.socket_.async_receive(
		boost::asio::buffer(
			c.new_data_
		),
		boost::bind(
			&server_impl::read_handler,
			this,
			_1,
			_2,
			boost::ref(c)
		)
	);

	handlers_++;
	accept();
}

void sanguis::net::detail::server_impl::handle_error(
	sge::string const &message,
	boost::system::error_code const &e,
	connection const &c)
{
	sge::string const error_msg(
		sge::iconv(
			e.message()
		)
	);

	// do we have an error or a disconnect...
	if (!detail::is_disconnect(e))
		throw sge::exception(
			message +
			SGE_TEXT(" error: ")+
			error_msg
		);

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("server: disconnected ")
			<< c.id_ 
			<< SGE_TEXT(" (")
			<< error_msg
			<< SGE_TEXT(")")
	);

	// ...else remove connection
	disconnect_signal_(
		c.id_,
		error_msg);

	connections_.erase_if(
		connections_.begin(),
		connections_.end(),
		&boost::lambda::_1 == &c);
}