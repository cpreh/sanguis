#ifndef SANGUIS_NET_CLIENT_HPP_INCLUDED
#define SANGUIS_NET_CLIENT_HPP_INCLUDED

#include "hostname_type.hpp"
#include "port_type.hpp"
#include "data_type.hpp"

#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/function/object_fwd.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/noncopyable.hpp>
#include <fcppt/string.hpp>


namespace sanguis
{
namespace net
{
namespace detail
{
class client_impl;
}

class client
{
	SGE_NONCOPYABLE(client)
public:
	typedef void connect_fun ();
	typedef void disconnect_fun (fcppt::string const &);
	typedef void data_fun (data_type const &);
	typedef fcppt::function::object<connect_fun> connect_function;
	typedef fcppt::function::object<disconnect_fun> disconnect_function;
	typedef fcppt::function::object<data_fun> data_function;

	client();
	void connect(
		hostname_type const &,
		port_type);
	void disconnect();
	void queue(
		data_type const &);
	void process();
	fcppt::signal::auto_connection register_connect(
		connect_function const &);
	fcppt::signal::auto_connection register_disconnect(
		disconnect_function const &);
	fcppt::signal::auto_connection register_data(
		data_function const &);
	~client();
private:
	sge::scoped_ptr<detail::client_impl> impl_;
};
}
}

#endif
