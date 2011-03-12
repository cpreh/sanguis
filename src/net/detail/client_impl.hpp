#ifndef SANGUIS_NET_DETAIL_CLIENT_IMPL_HPP_INCLUDED
#define SANGUIS_NET_DETAIL_CLIENT_IMPL_HPP_INCLUDED

#include "client_impl_fwd.hpp"
#include "circular_buffer.hpp"
#include "static_buffer.hpp"
#include "../client.hpp"
#include "../id_type.hpp"
#include "../data_type.hpp"
#include "../value_type.hpp"
#include "../port_type.hpp"
#include "../hostname_type.hpp"

#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/signal/object.hpp>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
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
	FCPPT_NONCOPYABLE(
		client_impl
	);
public:
	explicit client_impl(
		boost::asio::io_service &
	);

	~client_impl();

	void
	connect(
		hostname_type const &,
		port_type
	);

	void
	disconnect();

	void
	queue(
		data_type const &
	);

	fcppt::signal::auto_connection
	register_connect(
		client::connect_function const &
	);

	fcppt::signal::auto_connection
	register_disconnect(
		client::disconnect_function const &
	);

	fcppt::signal::auto_connection
	register_data(
		client::data_function const &
	);
private:
	// asio vars
	boost::asio::io_service &io_service_;

	boost::asio::ip::tcp::socket socket_;

	boost::asio::ip::tcp::resolver resolver_;

	fcppt::scoped_ptr<
		boost::asio::tcp::resolver::query
	> query_;

	// vars
	detail::static_buffer received_data_;

	detail::circular_buffer send_data_;

	// signals
	fcppt::signal::object<
		client::connect_fun
	> connect_signal_;

	fcppt::signal::object<
		client::disconnect_fun
	> disconnect_signal_;

	fcppt::signal::object<
		client::data_fun
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
};
}
}
}

#endif // SANGUIS_NET_DETAIL_CLIENT_IMPL_HPP_INCLUDED
