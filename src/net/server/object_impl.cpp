#include "server_impl.hpp"
#include "is_disconnect.hpp"
#include "connection.hpp"
#include "../log.hpp"
#include "../exception.hpp"
#undef max
// asio brings in window.h's max macro :(
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>

sanguis::net::detail::server_impl::server_impl()
:
	io_service_(),
	acceptor_(
		io_service_
	),
	id_counter_(
		static_cast<
			net::id::value_type
		>(
			0u
		)
	),
	new_connection_(),
	timer_duration_(
		_timer_duration
	),
	timer_(
		fcppt::make_unique_ptr<
			boost::asio::deadline_timer
		>(
			fcppt::ref(
				io_service_
			)
		)
	)
{
	timer_->expires_from_now(
		_timer_duration
	);

	timer_->async_wait(
		std::tr1::bind(
			&server_impl::handle_timeout,
			this,
			std::tr1::placeholders::_1
		)
	);
}

void 
sanguis::net::detail::server_impl::listen(
	port_type const _port
)
{
	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: listening on port ")
			<< _port
	);

	boost::asio::ip::tcp::endpoint const endpoint(
		boost::asio::ip::tcp::v4(),
		_port
	);

	acceptor_.open(
		endpoint.protocol()
	);

	acceptor_.set_option(
		boost::asio::ip::tcp::acceptor::reuse_address(
			true
		)
	);

	acceptor_.bind(
		endpoint
	);

	acceptor_.listen();

	this->accept();
}

void 
sanguis::net::detail::server_impl::queue(
	data_type const &_data
)
{
	BOOST_FOREACH(
		connection_container::reference con,
		connections_
	)
	{
		con.output().push_back(
			_data
		);

		if (c.sending_)
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
			std::tr1::bind(
				&server_impl::write_handler,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				std::tr1::ref(c)
			)
		);
	}
}

void
sanguis::net::detail::server_impl::queue(
	id_type const id,
	data_type const &s
)
{
	BOOST_FOREACH(
		connection_container::reference c,
		connections_)
	{
		if (c.id_ != id)
			continue;

		c.output_.push_back(
			s
		);

		if (c.sending_)
			return;
		c.sending_ = true;

		data_type const &out_data(
			c.output_.buffer()
		);

		c.socket_.async_send(
			boost::asio::buffer(
				out_data.data(),
				out_data.size()
			),
			std::tr1::bind(
				&server_impl::write_handler,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				std::tr1::ref(c)
			)
		);
		return;
	}

	// no valid id found?
	throw exception(
		FCPPT_TEXT("invalid id ")+
		fcppt::lexical_cast<
			fcppt::string
		>(
			id
		)
	);
}

fcppt::signal::auto_connection
sanguis::net::detail::server_impl::register_connect(
	server::connect_function const &f
)
{
	return connect_signal_.connect(
		f
	);
}

fcppt::signal::auto_connection
sanguis::net::detail::server_impl::register_disconnect(
	server::disconnect_function const &f)
{
	return disconnect_signal_.connect(
		f
	);
}

fcppt::signal::auto_connection 
sanguis::net::detail::server_impl::register_data(
	server::data_function const &f)
{
	return data_signal_.connect(
		f
	);
}

fcppt::signal::auto_connection 
sanguis::net::detail::server_impl::register_timer(
	server::timer_function const &_f)
{
	return timer_signal_.connect(
		_f);
}

void 
sanguis::net::detail::server_impl::run()
{
	io_service_.run();
}

void 
sanguis::net::detail::server_impl::stop()
{
	io_service_.stop();
}

void 
sanguis::net::detail::server_impl::accept()
{
	new_connection_.take(
		fcppt::make_unique_ptr<
			detail::connection
		>(
			net::id(
				id_counter_++
			),
			std::tr1::ref(
				io_service_
			)
		)
	);

	acceptor_.async_accept(
		new_connection_->socket(),
		std::tr1::bind(
			&server_impl::accept_handler,
			this,
			std::tr1::placeholders::_1
		)
	);
}

void 
sanguis::net::detail::server_impl::read_handler(
	boost::system::error_code const &e,
	std::size_t const bytes,
	connection &c
)
{
	if (e)
	{
		handle_error(FCPPT_TEXT("server read"),e,c);
		return;
	}

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: reading ")
			<< bytes 
			<< FCPPT_TEXT(" bytes.")
	);
	
	data_signal_(
		c.id_,
		data_type(
			c.new_data_.begin(),
			c.new_data_.begin() + bytes
		)
	);

	// receive some more
	c.socket_.async_receive(
		boost::asio::buffer(
			c.new_data_
		),
		std::tr1::bind(
			&server_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2,
			std::tr1::ref(
				c
			)
		)
	);
}

void 
sanguis::net::detail::server_impl::write_handler(
	boost::system::error_code const &e,
	std::size_t const bytes,
	connection &c)
{
	if (e)
	{
		handle_error(
			FCPPT_TEXT("server write"),
			e,
			c);
		return;
	}

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: wrote ")
			<< bytes 
			<< FCPPT_TEXT(" bytes.")
	);

	c.output_.erase(
		bytes
	);

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
		std::tr1::bind(
			&server_impl::write_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2,
			std::tr1::ref(c)
		)
	);
}

void 
sanguis::net::detail::server_impl::accept_handler(
	boost::system::error_code const &_error
)
{
	if(
		_error
	)
	{
		FCPPT_LOG_DEBUG(
			net::log(),
			fcppt::log::_
				<< FCPPT_TEXT("server: error while accepting")
		);

		this->accept();

		return;
	}

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: accepting a connection, id is ")
			<< new_connection_->id()
	);

	fcppt::container::ptr::push_back_unique_ptr(
		connections_,
		move(
			new_connection_
		)
	);
	
	detail::connection &current_con(
		connections_.back()
	);

	// send signal to handlers
	connect_signal_(
		current_conc.id()
	);

	current_con.socket_.async_receive(
		boost::asio::buffer(
			current_con.new_data()
		),
		std::tr1::bind(
			&server_impl::read_handler,
			this,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2,
			std::tr1::ref(
				current_con
			)
		)
	);

	this->accept();
}

void 
sanguis::net::detail::server_impl::handle_error(
	fcppt::string const &message,
	boost::system::error_code const &e,
	connection const &c
)
{
	fcppt::string const error_msg(
		fcppt::from_std_string(
			e.message()
		)
	);

	// do we have an error or a disconnect...
	if (!detail::is_disconnect(e))
		throw sge::exception(
			message +
			FCPPT_TEXT(" error: ")+
			error_msg
		);

	FCPPT_LOG_DEBUG(
		net::log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: disconnected ")
			<< c.id_ 
			<< FCPPT_TEXT(" (")
			<< error_msg
			<< FCPPT_TEXT(")")
	);

	// ...else remove connection
	disconnect_signal_(
		c.id_,
		error_msg
	);

	connections_.erase_if(
		connections_.begin(),
		connections_.end(),
		&boost::phoenix::arg_names::arg1 == &c
	);
}

void
sanguis::net::detail::server_impl::handle_timeout(
	boost::system::error_code const &_error
)
{
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("server: timeout "));

	if (_e)
	{
		FCPPT_LOG_DEBUG(
			log(),
			fcppt::log::_ << FCPPT_TEXT("server: error on timeout")
		);

		throw exception(
			fcppt::from_std_string(
				_e.message()
			)
		);
	}

	timer_signal_();

	timer_.reset(
		new boost::asio::deadline_timer(
			timer_->get_io_service()));

	timer_->expires_from_now(
		timer_duration_);
			
	timer_->async_wait(
		std::tr1::bind(
			&server_impl::handle_timeout,
			this,
			std::tr1::placeholders::_1
		)
	);
}
