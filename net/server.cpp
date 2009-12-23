#include "server.hpp"
#include "detail/server_impl.hpp"
#include "detail/connection.hpp"

sanguis::net::server::server()
	:	impl_(
	  	new detail::server_impl())
{}

fcppt::signal::auto_connection sanguis::net::server::register_connect(
	connect_function const &f)
{
	return impl_->register_connect(
		f);
}

fcppt::signal::auto_connection sanguis::net::server::register_disconnect(
	disconnect_function const &f)
{
	return impl_->register_disconnect(
		f);
}

fcppt::signal::auto_connection sanguis::net::server::register_data(
	data_function const &f)
{
	return impl_->register_data(
		f);
}

void sanguis::net::server::listen(
	port_type const port)
{
	return impl_->listen(port);
}

void sanguis::net::server::process()
{
	return impl_->process();
}

void sanguis::net::server::queue(
	id_type const _id,
	data_type const &_data)
{
	return impl_->queue(_id,_data);
}

sanguis::net::server::~server() {}
