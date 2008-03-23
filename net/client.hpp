#ifndef NET_CLIENT_HPP_INCLUDED
#define NET_CLIENT_HPP_INCLUDED

#include "types.hpp"
#include "output_buffer.hpp"

#include <asio.hpp>

#include <boost/function.hpp>
#include <boost/signal.hpp>

#include <string>
#include <iostream>

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
	typedef boost::signals::scoped_connection signal_connection;

	client();
	void connect(const address_type &,const port_type);
	void queue(const data_type &);
	void process();
	signal_connection register_connect(connect_function);
	signal_connection register_disconnect(disconnect_function);
	signal_connection register_data(data_function);

	private:
	typedef boost::array<data_type::value_type,4096> static_buffer;

	// asio vars
	asio::io_service &io_service;
	asio::ip::tcp::socket socket;
	asio::ip::tcp::resolver resolver;

	// vars
	std::size_t handlers;
	static_buffer new_data;
	output_buffer<data_type::value_type> output;
	bool connected,sending;

	// signals
	boost::signal<connect_fun> connect_signal;
	boost::signal<disconnect_fun> disconnect_signal;
	boost::signal<data_fun> data_signal;

	// handlers
	void handle_error(const string_type &,const asio::error_code &);
	void read_handler(const asio::error_code &,const std::size_t);
	void write_handler(const asio::error_code &,const std::size_t);
	void resolve_handler(const asio::error_code &,asio::ip::tcp::resolver::iterator);
	void connect_handler(const asio::error_code &,asio::ip::tcp::resolver::iterator);
};
}

#endif
