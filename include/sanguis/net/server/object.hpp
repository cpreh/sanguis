#ifndef SANGUIS_NET_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_NET_SERVER_OBJECT_HPP_INCLUDED

#include <sanguis/io_service_fwd.hpp>
#include <sanguis/net/server/object_impl_fwd.hpp>
#include <sanguis/net/server/connect_callback.hpp>
#include <sanguis/net/server/connection_id_container.hpp>
#include <sanguis/net/server/data_callback.hpp>
#include <sanguis/net/server/disconnect_callback.hpp>
#include <sanguis/net/server/timer_callback.hpp>
#include <sanguis/net/circular_buffer.hpp>
#include <sanguis/net/duration.hpp>
#include <sanguis/net/id.hpp>
#include <sanguis/net/port.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sanguis::io_service &,
		net::duration const &
	);

	~object();

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
	fcppt::scoped_ptr<
		server::object_impl
	> impl_;
};

}
}
}

#endif
