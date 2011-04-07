#ifndef SANGUIS_NET_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_NET_SERVER_OBJECT_HPP_INCLUDED

#include "object_impl_fwd.hpp"
#include "connect_callback.hpp"
#include "connection_id_container.hpp"
#include "data_callback.hpp"
#include "disconnect_callback.hpp"
#include "timer_callback.hpp"
#include "../circular_buffer.hpp"
#include "../id.hpp"
#include "../port.hpp"
#include <sge/time/duration.hpp>
#include <awl/mainloop/io_service_fwd.hpp>
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
		awl::mainloop::io_service &,
		sge::time::duration const &
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
