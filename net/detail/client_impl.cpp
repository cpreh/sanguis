#include "client_impl.hpp"
#include "is_disconnect.hpp"
#include "io_service_wrapper.hpp"
#include "../log.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

sanguis::net::detail::client_impl::client_impl() 
:
	io_service_(
		io_service_wrapper()
	),
	socket_(
		io_service_
	),
	resolver_(
		io_service_
	),
	handlers_(0),
	new_data_(),
	output_(),
	connected_(false),
	sending_(false),
	connect_signal_(),
	disconnect_signal_(),
	data_signal_()
{
	// TODO: put this in a single function
	//int flag = 1;
	//setsockopt(socket_.native(),IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
}

void sanguis::net::detail::client_impl::connect(
	hostname_type const &s,
	port_type const port)
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("client: resolving hostname ")
		             << sge::iconv(s) << SGE_TEXT(" on port")
								 << port);
	
	boost::asio::ip::tcp::resolver::query query(
		s,
		boost::lexical_cast<std::string>(
			port));
	resolver_.async_resolve(
		query,
		boost::bind(&client_impl::resolve_handler,this,_1,_2));
	handlers_++;
}

void sanguis::net::detail::client_impl::resolve_handler(
	boost::system::error_code const &e,
	boost::asio::ip::tcp::resolver::iterator i)
{
	if (e)
		throw sge::exception(
			SGE_TEXT("client: error resolving address: ")+
			sge::iconv(
				e.message()));

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("client: resolved domain, trying to connect"));
	
	boost::asio::ip::tcp::endpoint endpoint = *i;
	socket_.async_connect(
		endpoint,
		boost::bind(&client_impl::connect_handler,this,_1,++i));
	handlers_++;
}

void sanguis::net::detail::client_impl::connect_handler(
	boost::system::error_code const &e,
	boost::asio::ip::tcp::resolver::iterator i)
{
	handlers_--;
	if (e)
	{
		// are we at the end of the endpoint list?
		if (i == boost::asio::ip::tcp::resolver::iterator())
			throw sge::exception(
				SGE_TEXT("client: exhausted endpoints: ")+
				sge::iconv(
					e.message()));

		SGE_LOG_DEBUG(
			log(),
			sge::log::_1 << SGE_TEXT("client: resolving next endpoint"));
		
		boost::asio::ip::tcp::endpoint endpoint = *i;
		socket_.async_connect(
			endpoint,
			boost::bind(&client_impl::connect_handler,this,_1,++i));
		handlers_++;
		return;
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("client: connected"));

	// first connect to true, _then_ call signal
	connected_ = true;
	connect_signal_();
	socket_.async_receive(
		boost::asio::buffer(new_data_),
		boost::bind(&client_impl::read_handler,this,_1,_2));
	handlers_++;
}

void sanguis::net::detail::client_impl::handle_error(
	sge::string const &s,
	boost::system::error_code const &e)
{
	if (!detail::is_disconnect(e))
		throw sge::exception(
			SGE_TEXT("error in ")+
			s+
			SGE_TEXT(": ")+
			sge::iconv(
				e.message()));
		
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("client: disconnected (")
								 << sge::iconv(e.message()) 
								 << SGE_TEXT(")"));

	connected_ = false;
	disconnect_signal_(
		sge::iconv(
			e.message()));
}

void sanguis::net::detail::client_impl::read_handler(
	boost::system::error_code const &e,
	std::size_t const bytes)
{
	handlers_--;
	
	if (e)
	{
		handle_error(
			SGE_TEXT("client read"),
			e);
		return;
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("client: read")
								 << bytes << SGE_TEXT(" bytes"));

	data_signal_(
		data_type(
			new_data_.begin(),
			new_data_.begin()+bytes));

	socket_.async_receive(
		boost::asio::buffer(new_data_),
		boost::bind(&client_impl::read_handler,this,_1,_2));
	handlers_++;
}

void sanguis::net::detail::client_impl::queue(const data_type &data)
{
	output_.push_back(
		data);
}

void sanguis::net::detail::client_impl::write_handler(const boost::system::error_code &e,const std::size_t bytes)
{
	handlers_--;

	if (e)
	{
		handle_error(
			SGE_TEXT("client write"),
			e);
		return;
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("client: wrote ")
								 << bytes << SGE_TEXT(" bytes"));

	// are there bytes left to send?
	if (output_.finished(bytes).to_send())
	{
		socket_.async_send(
			boost::asio::buffer(
				output_.buffer()),
			boost::bind(&client_impl::write_handler,this,_1,_2));
		handlers_++;
	}
	else
	{
		// if no more data is present, set sending to false
		sending_ = false;
	}
}

void sanguis::net::detail::client_impl::process()
{
	if (connected_ && !sending_ && output_.to_send())
	{
		sending_ = true;
		socket_.async_send(
			boost::asio::buffer(output_.buffer()),
			boost::bind(&sanguis::net::detail::client_impl::write_handler,this,_1,_2));
		handlers_++;
	}

	if (!handlers_)
		return;

	boost::system::error_code e;
	io_service_.poll(e);
	if (e)
		throw sge::exception(
			SGE_TEXT("poll error: ")+
			sge::iconv(
				e.message()));
}

sge::signal::auto_connection sanguis::net::detail::client_impl::register_connect(client::connect_function const &f)
{
	return connect_signal_.connect(f);
}

sge::signal::auto_connection sanguis::net::detail::client_impl::register_disconnect(client::disconnect_function const &f)
{
	return disconnect_signal_.connect(f);
}

sge::signal::auto_connection sanguis::net::detail::client_impl::register_data(client::data_function const &f)
{
	return data_signal_.connect(f);
}

