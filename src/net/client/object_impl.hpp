#ifndef SANGUIS_NET_CLIENT_OBJECT_IMPL_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_OBJECT_IMPL_HPP_INCLUDED

#include "object_impl_fwd.hpp"
#include "connect_callback.hpp"
#include "connect_function.hpp"
#include "data_callback.hpp"
#include "data_function.hpp"
#include "error_callback.hpp"
#include "error_function.hpp"
#include "../circular_buffer.hpp"
#include "../static_buffer.hpp"
#include "../data_buffer.hpp"
#include "../port.hpp"
#include "../hostname.hpp"
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/string.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>

namespace sanguis
{
namespace net
{
namespace client
{

class object_impl
{
	FCPPT_NONCOPYABLE(
		object_impl
	);
public:
	explicit object_impl(
		boost::asio::io_service &
	);

	~object_impl();

	void
	connect(
		net::hostname const &,
		net::port
	);

	void
	disconnect();

	void
	queue(
		net::data_buffer const &
	);

	fcppt::signal::auto_connection
	register_connect(
		client::connect_callback const &
	);

	fcppt::signal::auto_connection
	register_error(
		client::error_callback const &
	);

	fcppt::signal::auto_connection
	register_data(
		client::data_callback const &
	);
private:
	// asio vars
	boost::asio::io_service &io_service_;

	boost::asio::ip::tcp::socket socket_;

	boost::asio::ip::tcp::resolver resolver_;

	fcppt::scoped_ptr<
		boost::asio::ip::tcp::resolver::query
	> query_;

	// vars
	net::static_buffer received_data_;

	net::circular_buffer send_data_;

	// signals
	fcppt::signal::object<
		client::connect_function
	> connect_signal_;

	fcppt::signal::object<
		client::error_function
	> error_signal_;

	fcppt::signal::object<
		client::data_function
	> data_signal_;

	// handlers
	void
	handle_error(
		fcppt::string const &,
		boost::system::error_code const &
	);

	void
	read_handler(
		boost::system::error_code const &,
		std::size_t
	);

	void
	write_handler(
		boost::system::error_code const &,
		std::size_t
	);

	void
	resolve_handler(
		boost::system::error_code const &,
		boost::asio::ip::tcp::resolver::iterator
	);

	void
	connect_handler(
		boost::system::error_code const &,
		boost::asio::ip::tcp::resolver::iterator
	);

	void
	send_data();

	void
	clear();

	static
	fcppt::log::object &
	log();
};

}
}
}

#endif
