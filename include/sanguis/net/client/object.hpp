#ifndef SANGUIS_NET_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_OBJECT_HPP_INCLUDED

#include <sanguis/io_service_fwd.hpp>
#include <sanguis/net/client/object_impl_fwd.hpp>
#include <sanguis/net/client/connect_callback.hpp>
#include <sanguis/net/client/data_callback.hpp>
#include <sanguis/net/client/error_callback.hpp>
#include <sanguis/net/circular_buffer.hpp>
#include <sanguis/net/hostname.hpp>
#include <sanguis/net/port.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace net
{
namespace client
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit object(
		sanguis::io_service &
	);

	~object();

	void
	connect(
		net::hostname const &,
		net::port
	);

	void
	disconnect();

	net::circular_buffer &
	send_buffer();

	void
	queue_send();

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
	fcppt::scoped_ptr<
		client::object_impl
	> impl_;
};

}
}
}

#endif
