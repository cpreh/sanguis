#ifndef NET_SERVER_HPP_INCLUDED
#define NET_SERVER_HPP_INCLUDED

#include "types.hpp"
#include "output_buffer.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>

#include <boost/function.hpp>
#include <boost/signal.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <string>
#include <iostream>
#include <fstream>

#include <cstddef>

namespace net
{
struct connection : boost::noncopyable
{
	// typedefs
	typedef boost::array<data_type::value_type,4096> static_buffer;

	const id_type id;
	boost::asio::ip::tcp::socket socket;
	static_buffer new_data;
	output_buffer<data_type::value_type> output;
	bool connected,sending;

	connection(const id_type id,boost::asio::io_service &io_service) 
		: id(id),socket(io_service),connected(false),sending(false) {}
};

class server : boost::noncopyable
{
	public:
	typedef void connect_fun (const id_type);
	typedef void disconnect_fun (const id_type,const string_type &);
	typedef void data_fun (const id_type,const data_type &);
	typedef boost::function<connect_fun> connect_function;
	typedef boost::function<disconnect_fun> disconnect_function;
	typedef boost::function<data_fun> data_function;
	typedef boost::signals::scoped_connection signal_connection;

	server();
	void listen(const port_type);
	void process();
	void queue(const id_type,const data_type &);
	void queue(const data_type &);
	signal_connection register_connect(connect_function);
	signal_connection register_disconnect(disconnect_function);
	signal_connection register_data(data_function);

	private:
	typedef boost::ptr_vector<connection> connection_container;

	// asio vars
	boost::asio::io_service &io_service;
	boost::asio::ip::tcp::acceptor acceptor;

	// vars
	id_type id_counter;
	connection_container connections;
	std::size_t handlers;

	// signals
	boost::signal<connect_fun> connect_signal;
	boost::signal<disconnect_fun> disconnect_signal;
	boost::signal<data_fun> data_signal;

	std::ofstream logstream;

	// private functions
	void accept();
	void read_handler(const boost::system::error_code &,const std::size_t,connection &);
	void write_handler(const boost::system::error_code &,const std::size_t,connection &);
	void accept_handler(const boost::system::error_code &,connection &);
	void handle_disconnect(const boost::system::error_code &,connection &);
	void handle_error(const string_type &,const boost::system::error_code &,const connection &);
};
}

#endif
