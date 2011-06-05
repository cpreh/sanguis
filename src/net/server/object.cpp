#include "object.hpp"
#include "object_impl.hpp"
#include <awl/mainloop/asio/io_service.hpp>
#include <fcppt/chrono/duration_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::net::server::object::object(
	awl::mainloop::io_service &_io_service,
	sge::time::duration const &_duration
)
:	
	impl_(
		fcppt::make_unique_ptr<
			server::object_impl
		>(
			fcppt::ref(
				dynamic_cast<
					awl::mainloop::asio::io_service &
				>(
					_io_service
				)
				.get()
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
