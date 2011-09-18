#include <sanguis/net/client/object.hpp>
#include <sanguis/net/client/object_impl.hpp>
#include <awl/mainloop/asio/io_service.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::net::client::object::object(
	awl::mainloop::io_service &_io_service
)
:
	impl_(
		fcppt::make_unique_ptr<
			client::object_impl
		>(
			fcppt::ref(
				dynamic_cast<
					awl::mainloop::asio::io_service &
				>(
					_io_service
				)
				.get()
			)
		)
	)
{
}

sanguis::net::client::object::~object()
{
}

void
sanguis::net::client::object::connect(
	net::hostname const &_host,
	net::port const _port
)
{
	return
		impl_->connect(
			_host,
			_port
		);
}

void
sanguis::net::client::object::disconnect()
{
	return impl_->disconnect();
}


sanguis::net::circular_buffer &
sanguis::net::client::object::send_buffer()
{
	return
		impl_->send_buffer();
}

void
sanguis::net::client::object::queue_send()
{
	impl_->queue_send();
}

fcppt::signal::auto_connection
sanguis::net::client::object::register_connect(
	client::connect_callback const &_callback
)
{
	return
		impl_->register_connect(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::net::client::object::register_error(
	client::error_callback const &_callback
)
{
	return
		impl_->register_error(
			_callback
		);
}

fcppt::signal::auto_connection
sanguis::net::client::object::register_data(
	client::data_callback const &_callback
)
{
	return
		impl_->register_data(
			_callback
		);
}
