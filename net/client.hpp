#ifndef NET_CLIENT_HPP_INCLUDED
#define NET_CLIENT_HPP_INCLUDED

#include "types.hpp"
#include "output_buffer.hpp"

#include <sge/signal/object.hpp>
#include <sge/signal/auto_connection.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>

#include <boost/tr1/array.hpp>
#include <boost/function.hpp>

#include <cstddef>

namespace net
{
struct client
{
	public:
	typedef void connect_fun ();
	typedef void disconnect_fun (const string_type &);
	typedef void data_fun (const data_type &);
	typedef boost::function<connect_fun> connect_function;
	typedef boost::function<disconnect_fun> disconnect_function;
	typedef boost::function<data_fun> data_function;
	typedef sge::signal::auto_connection signal_connection;

	client();
	void connect(const address_type &,const port_type);
	void queue(const data_type &);
	void process();
	signal_connection register_connect(connect_function);
	signal_connection register_disconnect(disconnect_function);
	signal_connection register_data(data_function);

	private:
	typedef std::tr1::array<data_type::value_type,4096> static_buffer;

	// asio vars
	boost::asio::io_service &io_service;
	boost::asio::ip::tcp::socket socket;
	boost::asio::ip::tcp::resolver resolver;

	// vars
	std::size_t handlers;
	static_buffer new_data;
	output_buffer<data_type::value_type> output;
	bool connected,sending;

	// signals
	sge::signal::object<connect_fun> connect_signal;
	sge::signal::object<disconnect_fun> disconnect_signal;
	sge::signal::object<data_fun> data_signal;

	// handlers
	void handle_error(const string_type &,const boost::system::error_code &);
	void read_handler(const boost::system::error_code &,const std::size_t);
	void write_handler(const boost::system::error_code &,const std::size_t);
	void resolve_handler(const boost::system::error_code &,boost::asio::ip::tcp::resolver::iterator);
	void connect_handler(const boost::system::error_code &,boost::asio::ip::tcp::resolver::iterator);
};
}

#endif
