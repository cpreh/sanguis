#include <sanguis/io_service.hpp>
#include <sanguis/io_service_impl.hpp>
#include <sanguis/net/server/object.hpp>
#include <sanguis/net/server/object_impl.hpp>
#include <sanguis/net/duration.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::net::server::object::object(
	sanguis::io_service &_io_service,
	net::duration const &_duration
)
:
	impl_(
		fcppt::make_unique_ptr<
			server::object_impl
		>(
			fcppt::ref(
				_io_service.impl().get()
			),
			_duration
		)
	)
{
}

sanguis::net::server::object::~object()
{
}

void
sanguis::net::server::object::listen(
	net::port const _port
)
{
	return
		impl_->listen(
			_port
		);
}

sanguis::net::circular_buffer *
sanguis::net::server::object::send_buffer(
	net::id const _id
)
{
	return
		impl_->send_buffer(
			_id
		);
}

sanguis::net::server::connection_id_container const
sanguis::net::server::object::connections() const
{
	return
		impl_->connections();
}

void
sanguis::net::server::object::queue_send(
	net::id const _id
)
{
	return
		impl_->queue_send(
			_id
		);
}

fcppt::signal::auto_connection
sanguis::net::server::object::register_connect(
	server::connect_callback const &_callback
)
{
	return
		impl_->register_connect(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::net::server::object::register_disconnect(
	server::disconnect_callback const &_callback
)
{
	return
		impl_->register_disconnect(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::net::server::object::register_data(
	server::data_callback const &_callback
)
{
	return
		impl_->register_data(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::net::server::object::register_timer(
	server::timer_callback const &_callback
)
{
	return
		impl_->register_timer(
			_callback
		);
}

void
sanguis::net::server::object::stop()
{
	return
		impl_->stop();
}
