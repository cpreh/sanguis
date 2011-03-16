#include "object.hpp"
#include "object_impl.hpp"
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

void
sanguis::net::client::object::queue(
	net::data_buffer const &_data
)
{
	return
		impl_->queue(
			_data
		);
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
sanguis::net::client::object::register_disconnect(
	client::disconnect_callback const &_callback
)
{
	return
		impl_->register_disconnect(
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
