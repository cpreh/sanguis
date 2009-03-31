#ifndef NET_SERVER_HPP_INCLUDED
#define NET_SERVER_HPP_INCLUDED

#include "id_type.hpp"
#include "data_type.hpp"
#include "port_type.hpp"
#include "output_buffer.hpp"

#include <sge/string.hpp>
#include <sge/signal/object.hpp>
#include <sge/noncopyable.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>

#include <boost/function.hpp>
#include <boost/tr1/array.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <cstddef>

namespace sanguis
{
namespace net
{

// TODO: put this in a file
class connection {
	SGE_NONCOPYABLE(connection)
public:
	// typedefs
	typedef std::tr1::array<data_type::value_type,4096> static_buffer;

	const id_type id;
	boost::asio::ip::tcp::socket socket;
	static_buffer new_data;
	output_buffer<data_type::value_type> output;
	bool connected,sending;

	connection(const id_type id,boost::asio::io_service &io_service) 
		: id(id),socket(io_service),connected(false),sending(false) {}
};

class server {
	SGE_NONCOPYABLE(server)
public:
	typedef void connect_fun (const id_type);
	typedef void disconnect_fun (const id_type,sge::string const &);
	typedef void data_fun (const id_type,const data_type &);
	typedef boost::function<connect_fun> connect_function;
	typedef boost::function<disconnect_fun> disconnect_function;
	typedef boost::function<data_fun> data_function;

	server();
	void listen(const port_type);
	void process();
	void queue(const id_type,const data_type &);
	void queue(const data_type &);
	sge::signal::auto_connection register_connect(connect_function);
	sge::signal::auto_connection register_disconnect(disconnect_function);
	sge::signal::auto_connection register_data(data_function);

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
	sge::signal::object<connect_fun> connect_signal;
	sge::signal::object<disconnect_fun> disconnect_signal;
	sge::signal::object<data_fun> data_signal;

	// private functions
	void accept();
	void read_handler(const boost::system::error_code &,const std::size_t,connection &);
	void write_handler(const boost::system::error_code &,const std::size_t,connection &);
	void accept_handler(const boost::system::error_code &,connection &);
	void handle_disconnect(const boost::system::error_code &,connection &);
	void handle_error(sge::string const &,const boost::system::error_code &,const connection &);
};
}
}

#endif
