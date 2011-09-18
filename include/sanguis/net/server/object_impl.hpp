#ifndef SANGUIS_NET_SERVER_OBJECT_IMPL_HPP_INCLUDED
#define SANGUIS_NET_SERVER_OBJECT_IMPL_HPP_INCLUDED

#include <sanguis/net/server/object_impl_fwd.hpp>
#include <sanguis/net/server/connect_callback.hpp>
#include <sanguis/net/server/connect_function.hpp>
#include <sanguis/net/server/connection_container.hpp>
#include <sanguis/net/server/connection_id_container.hpp>
#include <sanguis/net/server/connection_fwd.hpp>
#include <sanguis/net/server/data_callback.hpp>
#include <sanguis/net/server/data_function.hpp>
#include <sanguis/net/server/disconnect_callback.hpp>
#include <sanguis/net/server/disconnect_function.hpp>
#include <sanguis/net/server/timer_callback.hpp>
#include <sanguis/net/server/timer_function.hpp>
#include <sanguis/net/circular_buffer.hpp>
#include <sanguis/net/duration.hpp>
#include <sanguis/net/id.hpp>
#include <sanguis/net/port.hpp>
#include <fcppt/chrono/asio/deadline_timer.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

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
	object_impl(
		boost::asio::io_service &,
		net::duration const &
	);

	~object_impl();

	void
	listen(
		net::port
	);

	net::circular_buffer *
	send_buffer(
		net::id
	);

	server::connection_id_container const
	connections() const;

	void
	queue_send(
		net::id
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

	fcppt::signal::auto_connection
	register_timer(
		server::timer_callback const &
	);

	void
	stop();
private:
	boost::asio::io_service &io_service_;

	boost::asio::ip::tcp::acceptor acceptor_;

	net::id::value_type id_counter_;

	fcppt::unique_ptr<
		server::connection
	> new_connection_;

	server::connection_container connections_;

	fcppt::signal::object<
		server::connect_function
	> connect_signal_;

	fcppt::signal::object<
		server::disconnect_function
	> disconnect_signal_;

	fcppt::signal::object<
		server::data_function
	> data_signal_;

	fcppt::signal::object<
		server::timer_function
	> timer_signal_;

	net::duration const timer_duration_;

	fcppt::chrono::asio::deadline_timer deadline_timer_;

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
	timer_handler();

	void
	send_data(
		server::connection &
	);

	void
	receive_data(
		server::connection &
	);

	void
	reset_timer();

	server::connection &
	connection(
		net::id
	);
};

}
}
}

#endif
