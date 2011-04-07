#ifndef SANGUIS_NET_SERVER_OBJECT_IMPL_HPP_INCLUDED
#define SANGUIS_NET_SERVER_OBJECT_IMPL_HPP_INCLUDED

#include "object_impl_fwd.hpp"
#include "connect_callback.hpp"
#include "connect_function.hpp"
#include "connection_container.hpp"
#include "connection_id_container.hpp"
#include "connection_fwd.hpp"
#include "data_callback.hpp"
#include "data_function.hpp"
#include "disconnect_callback.hpp"
#include "disconnect_function.hpp"
#include "timer_callback.hpp"
#include "timer_function.hpp"
#include "../circular_buffer.hpp"
#include "../id.hpp"
#include "../port.hpp"
#include <sge/time/duration.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/system/error_code.hpp>
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
	object_impl(
		boost::asio::io_service &,
		sge::time::duration const &
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

	boost::posix_time::milliseconds const timer_duration_;

	boost::asio::deadline_timer deadline_timer_;

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

	static
	fcppt::log::object &
	log();
};

}
}
}

#endif
