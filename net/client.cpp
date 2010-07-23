#include "detail/client_impl.hpp"
#include <sge/mainloop/asio/io_service.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>

sanguis::net::client::client(
	sge::mainloop::io_service_ptr const _io_service
)
:
	impl_(
		new detail::client_impl(
			fcppt::dynamic_pointer_cast<
				sge::mainloop::asio::io_service
			>(
				_io_service
			)
			->get()
		)
	)
{
}

void
sanguis::net::client::connect(
	hostname_type const &s,
	port_type const port
)
{
	return impl_->connect(s,port);
}

void
sanguis::net::client::disconnect()
{
	return impl_->disconnect();
}

void
sanguis::net::client::queue(
	data_type const &data
)
{
	return impl_->queue(data);
}

void
sanguis::net::client::process()
{
	return impl_->process();
}

fcppt::signal::auto_connection
sanguis::net::client::register_connect(
	connect_function const &f
)
{
	return impl_->register_connect(f);
}

fcppt::signal::auto_connection
sanguis::net::client::register_disconnect(
	disconnect_function const &f
)
{
	return impl_->register_disconnect(f);
}

fcppt::signal::auto_connection
sanguis::net::client::register_data(
	data_function const &f
)
{
	return impl_->register_data(f);
}

// has to be here because of impl_
sanguis::net::client::~client()
{}
