#include "is_disconnect.hpp"
#include "client.hpp"
#include "exception.hpp"
#include "io_service_wrapper.hpp"
#include <boost/asio/buffer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

net::client::client() 
	: io_service(io_service_wrapper()),socket(io_service),
	  resolver(io_service),connected(false),sending(false) 
{
	// TODO: put this in a single function
	int flag = 1;
	setsockopt(socket.native(),IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(int));
}

void net::client::connect(const address_type &s,const port_type port)
{
	//asio::ip::tcp::resolver::query query(s,boost::lexical_cast<std::string>(port),
	//	asio::ip::tcp::resolver::query::address_configured | 
	//		asio::ip::tcp::resolver::query::numeric_service);

#ifdef NET_LOG
	std::clog << "net_client: resolving hostname " << s << " on port " << port << "\n";
#endif
	
	boost::asio::ip::tcp::resolver::query query(s,boost::lexical_cast<std::string>(port));
	resolver.async_resolve(query,boost::bind(&client::resolve_handler,this,_1,_2));
	handlers++;
}

void net::client::resolve_handler(const boost::system::error_code &e,boost::asio::ip::tcp::resolver::iterator i)
{
	if (e)
		throw exception("net_client: error resolving address: "+e.message());

#ifdef NET_LOG
	std::clog << "net_client: resolved domain, trying to connect...\n";
#endif
	
	boost::asio::ip::tcp::endpoint endpoint = *i;
	socket.async_connect(endpoint,boost::bind(&client::connect_handler,this,_1,++i));
	handlers++;
}

void net::client::connect_handler(const boost::system::error_code &e,boost::asio::ip::tcp::resolver::iterator i)
{
	handlers--;
	if (e)
	{
		// are we at the end of the endpoint list?
		if (i == boost::asio::ip::tcp::resolver::iterator())
			throw exception("net_client: exhausted endpoints: "+e.message());

#ifdef NET_LOG
		std::clog << "net_client: resolving next endpoint\n";
#endif
		
		boost::asio::ip::tcp::endpoint endpoint = *i;
		socket.async_connect(endpoint,boost::bind(&client::connect_handler,this,_1,++i));
		handlers++;
		return;
	}

#ifdef NET_LOG
	std::clog << "net_client: connected\n";
#endif

	/*
	asio::socket_base::receive_buffer_size option(1);
	socket.set_option(option);

	asio::socket_base::send_buffer_size option_b(1);
	socket.set_option(option_b);
	*/

	// first connect to true, _then_ call signal
	connected = true;
	connect_signal();
	socket.async_receive(boost::asio::buffer(new_data),boost::bind(&client::read_handler,this,_1,_2));
	handlers++;
}

void net::client::handle_error(const string_type &s,const boost::system::error_code &e)
{
	if (is_disconnect(e))
	{
#ifdef NET_LOG
		std::clog << "net_client: disconnected (" << e.message() << ")\n";
#endif
		connected = false;
		disconnect_signal(e.message());
		return;
	}

	throw exception("error in "+s+": "+e.message());
}

void net::client::read_handler(const boost::system::error_code &e,const std::size_t bytes)
{
	handlers--;
	
	if (e)
	{
		handle_error("client read",e);
		return;
	}

#ifdef NET_LOG
		std::clog << "net_client: read " << bytes << " bytes\n";
#endif

	data_signal(data_type(new_data.begin(),new_data.begin()+bytes));
	socket.async_receive(boost::asio::buffer(new_data),boost::bind(&client::read_handler,this,_1,_2));
	handlers++;
}

void net::client::queue(const data_type &data)
{
	output.push_back(data);
}

void net::client::write_handler(const boost::system::error_code &e,const std::size_t bytes)
{
	handlers--;

	if (e)
	{
		handle_error("client write",e);
		return;
	}

#ifdef NET_LOG
	std::clog << "net_client: wrote " << bytes << " bytes\n";
#endif

	// are there bytes left to send?
	if (output.finished(bytes).to_send())
	{
		socket.async_send(boost::asio::buffer(output.buffer()),
			boost::bind(&client::write_handler,this,_1,_2));
		handlers++;
	}
	else
	{
		// if no more data is present, set sending to false
		sending = false;
	}
}

void net::client::process()
{
	if (connected && !sending && output.to_send())
	{
		sending = true;
		socket.async_send(boost::asio::buffer(output.buffer()),
			boost::bind(&net::client::write_handler,this,_1,_2));
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

net::client::signal_connection net::client::register_connect(connect_function f)
{
	return connect_signal.connect(f);
}

net::client::signal_connection net::client::register_disconnect(disconnect_function f)
{
	return disconnect_signal.connect(f);
}

net::client::signal_connection net::client::register_data(data_function f)
{
	return data_signal.connect(f);
}
