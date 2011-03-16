#include "object.hpp"
#include "object_impl.hpp"
#include <awl/mainloop/asio/io_service.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::net::server::object::object(
	awl::mainloop::io_service &_io_service
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
			)
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

void 
sanguis::net::server::object::queue(
	net::id const _id,
	net::data_buffer const &_data
)
{
	return 
		impl_->queue(
			_id,
			_data
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

void 
sanguis::net::server::object::stop()
{
	return 
		impl_->stop();
}
