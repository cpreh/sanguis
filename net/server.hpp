#ifndef SANGUIS_NET_SERVER_HPP_INCLUDED
#define SANGUIS_NET_SERVER_HPP_INCLUDED

#include "detail/server_impl_fwd.hpp"
#include "id_type.hpp"
#include "data_type.hpp"
#include "port_type.hpp"

#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/function/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <boost/date_time.hpp>

namespace sanguis
{
namespace net
{

class server {
	FCPPT_NONCOPYABLE(server)
public:
	typedef void connect_fun (id_type);
	typedef void disconnect_fun (id_type,fcppt::string const &);
	typedef void data_fun (id_type,data_type const &);
	typedef void timer_fun ();
	typedef fcppt::function::object<connect_fun> connect_function;
	typedef fcppt::function::object<disconnect_fun> disconnect_function;
	typedef fcppt::function::object<data_fun> data_function;
	typedef fcppt::function::object<timer_fun> timer_function;
	typedef boost::posix_time::milliseconds time_resolution;

	explicit
	server(
		time_resolution const &);

	void
	listen(
		port_type
	);

	void
	process();

	void
	queue(
		id_type,
		data_type const &);

	void
	queue(
		data_type const &);

	fcppt::signal::auto_connection
	register_connect(
		connect_function const &);

	fcppt::signal::auto_connection
	register_disconnect(
		disconnect_function const &);

	fcppt::signal::auto_connection
	register_data(
		data_function const &);
	
	fcppt::signal::auto_connection
	register_timer(
		timer_function const &);

	void 
	run();

	void 
	stop();

	~server();
private:
	fcppt::scoped_ptr<detail::server_impl> impl_;
};
}
}

#endif
