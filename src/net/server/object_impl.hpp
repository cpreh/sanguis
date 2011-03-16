#ifndef SANGUIS_NET_SERVER_OBJECT_IMPL_HPP_INCLUDED
#define SANGUIS_NET_SERVER_OBJECT_IMPL_HPP_INCLUDED

#include "object_impl_fwd.hpp"
#include "connect_callback.hpp"
#include "connect_function.hpp"
#include "connection_fwd.hpp"
#include "data_callback.hpp"
#include "data_function.hpp"
#include "disconnect_callback.hpp"
#include "disconnect_function.hpp"
#include "../data_buffer.hpp"
#include "../id.hpp"
#include "../port.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/system/error_code.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr.hpp>
#include <cstddef>

namespace sanguis
{
namespace net
{
namespace server
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
	listen(
		net::port
	);

	void
	queue(
		net::id,
		net::data_buffer const &
	);

	fcppt::signal::auto_connection
	register_connect(
		server::connect_callback const &
	);

	fcppt::signal::auto_connection
	register_disconnect(
		server::disconnect_callback const &
	);
	
	fcppt::signal::auto_connection
	register_data(
		server::data_callback const &
	);

	void
	stop();
private:
	typedef boost::ptr_map<
		net::id,
		server::connection
	> connection_container;

	boost::asio::io_service &io_service_;

	boost::asio::ip::tcp::acceptor acceptor_;

	net::id::value_type id_counter_;

	fcppt::unique_ptr<
		connection
	> new_connection_;

	connection_container connections_;

	fcppt::signal::object<
		server::connect_function
	> connect_signal_;

	fcppt::signal::object<
		server::disconnect_function
	> disconnect_signal_;

	fcppt::signal::object<
		server::data_function
	> data_signal_;

	void
	accept();

	void
	read_handler(
		boost::system::error_code const &,
		std::size_t,
		server::connection &
	);

	void
	write_handler(
		boost::system::error_code const &,
		std::size_t,
		server::connection &
	);

	void
	accept_handler(
		boost::system::error_code const &
	);

	void
	handle_error(
		fcppt::string const &,
		boost::system::error_code const &,
		server::connection const &
	);

	void
	send_data(
		server::connection &
	);
};

}
}
}

#endif
