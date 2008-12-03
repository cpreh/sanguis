#include "server.hpp"
#include "exception.hpp"
#include "is_disconnect.hpp"
#include "io_service_wrapper.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/ref.hpp>
#include <iostream>

net::server::server()
	: io_service(io_service_wrapper()),acceptor(io_service),id_counter(0),handlers(0),logstream("server.log") {}

net::server::signal_connection net::server::register_connect(connect_function f)
{
	return connect_signal.connect(f);
}

net::server::signal_connection net::server::register_disconnect(disconnect_function f)
{
	return disconnect_signal.connect(f);
}

net::server::signal_connection net::server::register_data(data_function f)
{
	return data_signal.connect(f);
}

void net::server::listen(const port_type port)
{
#ifdef NET_LOG
	std::cerr << "net_server: listening on port " << port << "\n";
#endif

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	acceptor.open(endpoint.protocol());
	acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor.bind(endpoint);
	acceptor.listen();

	accept();
}

void net::server::accept()
{
	connections.push_back(new connection(id_counter++,io_service));
	connection &c = connections.back();

	acceptor.async_accept(c.socket,
		boost::bind(&server::accept_handler,this,_1,boost::ref(c)));
	handlers++;
}

void net::server::accept_handler(const boost::system::error_code &e,connection &c)
{
	handlers--;

	if (e)
	{
#ifdef NET_LOG
		std::cerr << "net_server: error while accepting...\n";
#endif
		throw exception(e.message());
	}

#ifdef NET_LOG
	std::clog << "net_server: accepting a connection\n";
#endif

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

void net::server::handle_error(const string_type &message,
	const boost::system::error_code &e,const connection &c)
{
	// do we have an error or a disconnect...
	if (!is_disconnect(e))
		throw exception(message+" error: "+e.message());

#ifdef NET_LOG
	std::clog << "net_server: disconnected " << c.id << " (" << e.message() << ")\n";
#endif

	// ...else remove connection
	disconnect_signal(c.id,e.message());
	connections.erase_if(connections.begin(),connections.end(),&boost::lambda::_1 == &c);
}

void net::server::write_handler(const boost::system::error_code &e,
	const std::size_t bytes,connection &c)
{
	handlers--;

	if (e)
	{
		handle_error("server write",e,c);
		return;
	}

#ifdef NET_LOG
	std::clog << "net_server: wrote " << bytes << " bytes\n";
#endif

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

void net::server::read_handler(const boost::system::error_code &e,
	const std::size_t bytes,connection &c)
{
	handlers--;

	if (e)
	{
		handle_error("server read",e,c);
		return;
	}

#ifdef NET_LOG
	std::clog << "net_server: reading " << bytes << " bytes\n";
#endif
	
	data_signal(c.id,data_type(c.new_data.begin(),c.new_data.begin() + bytes));

	// receive some more
	c.socket.async_receive(boost::asio::buffer(c.new_data),
		boost::bind(&net::server::read_handler,this,_1,_2,boost::ref(c)));
	handlers++;
}

void net::server::queue(const data_type &s)
{
	logstream << s << "\n";
	
	// send to all clients
	for (connection_container::iterator i = connections.begin(); 
		i != connections.end(); ++i)
	{
		if (!i->connected)
			continue;

		i->output.push_back(s);
	}
}

void net::server::queue(const id_type id,const data_type &s)
{
	logstream << s << "\n";

	for (connection_container::iterator i = connections.begin(); 
		i != connections.end(); ++i)
	{
		if (i->id != id)
			continue;

		if (!i->connected)
			throw exception("invalid id "+boost::lexical_cast<string_type>(id));

		i->output.push_back(s);
		return;
	}

	// no valid id found?
	throw exception("invalid id "+boost::lexical_cast<string_type>(id));
}

void net::server::process()
{
	for (connection_container::iterator i = connections.begin(); 
		i != connections.end(); ++i)
	{
		if (i->sending || !i->output.to_send())
			continue;

		i->sending = true;
		i->socket.async_send(boost::asio::buffer(i->output.buffer()),
			boost::bind(&net::server::write_handler,this,_1,_2,boost::ref(*i)));
		handlers++;
	}

	if (handlers)
	{
		boost::system::error_code e;
		io_service.poll(e);
		if (e)
			throw exception("poll error: "+e.message());
	}
}
