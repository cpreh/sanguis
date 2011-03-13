#ifndef SANGUIS_NET_CLIENT_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_HPP_INCLUDED

#include "detail/client_impl_fwd.hpp"
#include "hostname_type.hpp"
#include "port_type.hpp"
#include "data_type.hpp"

#include <awl/mainloop/io_service_fwd.hpp>

#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/function/object_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace net
{

class client
{
	FCPPT_NONCOPYABLE(
		client
	);
public:
	typedef void connect_fun ();

	typedef void disconnect_fun (fcppt::string const &);

	typedef void data_fun (data_type const &);

	typedef fcppt::function::object<connect_fun> connect_function;

	typedef fcppt::function::object<disconnect_fun> disconnect_function;

	typedef fcppt::function::object<data_fun> data_function;

	explicit client(
		awl::mainloop::io_service &
	);

	void
	connect(
		hostname_type const &,
		port_type
	);

	void
	disconnect();

	void
	queue(
		data_type const &
	);

	void
	process();

	fcppt::signal::auto_connection
	register_connect(
		connect_function const &
	);

	fcppt::signal::auto_connection
	register_disconnect(
		disconnect_function const &
	);

	fcppt::signal::auto_connection
	register_data(
		data_function const &
	);

	~client();
private:
	fcppt::scoped_ptr<
		detail::client_impl
	> impl_;
};
}
}

#endif
