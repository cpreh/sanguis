#include "server.hpp"
#include "detail/server_impl.hpp"
#include "detail/connection.hpp"

sanguis::net::server::server(
	time_resolution const &_r)
:	
	impl_(
	 	new detail::server_impl(
			_r))
{}

fcppt::signal::auto_connection 
sanguis::net::server::register_connect(
	connect_function const &_f)
{
	return 
		impl_->register_connect(
			_f);
}

fcppt::signal::auto_connection 
sanguis::net::server::register_disconnect(
	disconnect_function const &_f)
{
	return 
		impl_->register_disconnect(
			_f);
}

fcppt::signal::auto_connection 
sanguis::net::server::register_data(
	data_function const &_f)
{
	return 
		impl_->register_data(
			_f);
}

void 
sanguis::net::server::listen(
	port_type const _port)
{
	return 
		impl_->listen(
			_port);
}

void 
sanguis::net::server::process()
{
	return 
		impl_->process();
}

void 
sanguis::net::server::queue(
	id_type const _id,
	data_type const &_data)
{
	return 
		impl_->queue(
			_id,
			_data);
}

void 
sanguis::net::server::run()
{
	return 
		impl_->run();
}

void 
sanguis::net::server::stop()
{
	return 
		impl_->stop();
}

sanguis::net::server::~server() {}
