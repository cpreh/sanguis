#include "server.hpp"
#include "detail/is_disconnect.hpp"
#include "detail/io_service_wrapper.hpp"
#include "log.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/ref.hpp>
#include <iostream>

sanguis::net::server::server()
:
	io_service(
		detail::io_service_wrapper()
	),
	acceptor(
		io_service
	),
	id_counter(0),
	handlers(0)
{}

sge::signal::auto_connection sanguis::net::server::register_connect(connect_function f)
{
	return connect_signal.connect(f);
}

sge::signal::auto_connection sanguis::net::server::register_disconnect(disconnect_function f)
{
	return disconnect_signal.connect(f);
}

sge::signal::auto_connection sanguis::net::server::register_data(data_function f)
{
	return data_signal.connect(f);
}

void sanguis::net::server::listen(const port_type port)
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("server: listening on port ")
		             << port);

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	acceptor.open(endpoint.protocol());
	acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor.bind(endpoint);
	acceptor.listen();

	accept();
}

void sanguis::net::server::accept()
{
	connections.push_back(new connection(id_counter++,io_service));
	connection &c = connections.back();

	acceptor.async_accept(c.socket,
		boost::bind(&server::accept_handler,this,_1,boost::ref(c)));
	handlers++;
}

void sanguis::net::server::accept_handler(const boost::system::error_code &e,connection &c)
{
	handlers--;

	if (e)
	{
		SGE_LOG_DEBUG(
			log(),
			sge::log::_1 << SGE_TEXT("server: error while accepting"));
		throw sge::exception(sge::iconv(e.message()));
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("server: accepting a connection"));

	// FIXME
	//int flag = 1;
	//setsockopt(c.socket.native(), IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
	
	/*
	asio::socket_base::receive_buffer_size option(1);
	c.socket.set_option(option);

	asio::socket_base::send_buffer_size option_b(1);
	c.socket.set_option(option_b);
	*/

	// first set connected, _then_ call handler 
	// (else queueing code in the handler can't work)
	c.connected = true;

	// send signal to handlers
	connect_signal(c.id);

	c.socket.async_receive(boost::asio::buffer(c.new_data),
		boost::bind(&server::read_handler,this,_1,_2,boost::ref(c)));
	handlers++;
	accept();
}

void sanguis::net::server::handle_error(
	const sge::string &message,
	const boost::system::error_code &e,
	const connection &c)
{
	// do we have an error or a disconnect...
	if (!detail::is_disconnect(e))
		throw sge::exception(
			sge::iconv(message)+
			SGE_TEXT(" error: ")+
			sge::iconv(e.message()));

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("server: disconnected ")
		             << c.id << SGE_TEXT(" (")
								 << sge::iconv(e.message()) << SGE_TEXT(")"));

	// ...else remove connection
	disconnect_signal(c.id,e.message());
	connections.erase_if(connections.begin(),connections.end(),&boost::lambda::_1 == &c);
}

void sanguis::net::server::write_handler(const boost::system::error_code &e,
	const std::size_t bytes,connection &c)
{
	handlers--;

	if (e)
	{
		handle_error("server write",e,c);
		return;
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("server: wrote ")
		             << bytes << SGE_TEXT(" bytes."));

	// are there bytes left to send?
	if (c.output.finished(bytes).to_send())
	{
		c.socket.async_send(boost::asio::buffer(c.output.buffer()),
			boost::bind(&server::write_handler,this,_1,_2,boost::ref(c)));
		handlers++;
	}
	else
	{
		// if no more data is present, set sending to false
		c.sending = false;
	}
}

void sanguis::net::server::read_handler(const boost::system::error_code &e,
	const std::size_t bytes,connection &c)
{
	handlers--;

	if (e)
	{
		handle_error("server read",e,c);
		return;
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("server: reading ")
		             << bytes << SGE_TEXT(" bytes."));
	
	data_signal(c.id,data_type(c.new_data.begin(),c.new_data.begin() + bytes));

	// receive some more
	c.socket.async_receive(boost::asio::buffer(c.new_data),
		boost::bind(&sanguis::net::server::read_handler,this,_1,_2,boost::ref(c)));
	handlers++;
}

void sanguis::net::server::queue(const data_type &s)
{
	// send to all clients
	for (connection_container::iterator i = connections.begin(); 
		i != connections.end(); ++i)
	{
		if (!i->connected)
			continue;

		i->output.push_back(s);
	}
}

void sanguis::net::server::queue(const id_type id,const data_type &s)
{
	for (connection_container::iterator i = connections.begin(); 
		i != connections.end(); ++i)
	{
		if (i->id != id)
			continue;

		if (!i->connected)
			throw sge::exception(SGE_TEXT("invalid id ")+boost::lexical_cast<sge::string>(id));

		i->output.push_back(s);
		return;
	}

	// no valid id found?
	throw sge::exception(SGE_TEXT("invalid id ")+boost::lexical_cast<sge::string>(id));
}

void sanguis::net::server::process()
{
	for (connection_container::iterator i = connections.begin(); 
		i != connections.end(); ++i)
	{
		if (i->sending || !i->output.to_send())
			continue;

		i->sending = true;
		i->socket.async_send(boost::asio::buffer(i->output.buffer()),
			boost::bind(&sanguis::net::server::write_handler,this,_1,_2,boost::ref(*i)));
		handlers++;
	}

	if (handlers)
	{
		boost::system::error_code e;
		io_service.poll(e);
		if (e)
			throw sge::exception(SGE_TEXT("poll error: ")+sge::iconv(e.message()));
	}
}
