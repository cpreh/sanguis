#ifndef SANGUIS_NET_DETAIL_CLIENT_IMPL_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_CLIENT_IMPL_HPP_INCLUDED

#include "../client.hpp"
#include "../id_type.hpp"
#include "../data_type.hpp"
#include "../port_type.hpp"
#include "../hostname_type.hpp"
#include "output_buffer_decl.hpp"

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
namespace detail
{
class client_impl
{
SGE_NONCOPYABLE(client_impl)
public:
	client_impl();
	void connect(
		hostname_type const &,
		port_type);
	void queue(
		data_type const &);
	void process();
	sge::signal::auto_connection register_connect(
		client::connect_function const &);
	sge::signal::auto_connection register_disconnect(
		client::disconnect_function const &);
	sge::signal::auto_connection register_data(
		client::data_function const &);
private:
	typedef std::tr1::array<
		data_type::value_type,
		4096> static_buffer;

	// asio vars
	boost::asio::io_service &io_service_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::resolver resolver_;

	// vars
	unsigned handlers_;
	static_buffer new_data_;
	output_buffer<data_type::value_type> output_;
	bool connected_,sending_;

	// signals
	sge::signal::object<client::connect_fun> connect_signal_;
	sge::signal::object<client::disconnect_fun> disconnect_signal_;
	sge::signal::object<client::data_fun> data_signal_;

	// handlers
	void handle_error(
		sge::string const &,
		boost::system::error_code const &);
	void read_handler(
		boost::system::error_code const &,
		std::size_t);
	void write_handler(
		boost::system::error_code const &,
		std::size_t);
	void resolve_handler(
		boost::system::error_code const &,
		boost::asio::ip::tcp::resolver::iterator);
	void connect_handler(
		boost::system::error_code const &,
		boost::asio::ip::tcp::resolver::iterator);
};
}
}
}

#endif // SANGUIS_NET_DETAIL_CLIENT_IMPL_HPP_INCLUDED
