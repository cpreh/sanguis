#ifndef SANGUIS_NET_SERVER_HPP_INCLUDED
#define SANGUIS_NET_SERVER_HPP_INCLUDED

#include "id_type.hpp"
#include "data_type.hpp"
#include "port_type.hpp"

#include <sge/signal/auto_connection.hpp>
#include <sge/noncopyable.hpp>
#include <sge/string.hpp>
#include <sge/scoped_ptr.hpp>

#include <boost/function.hpp>

namespace sanguis
{
namespace net
{
namespace detail
{
class server_impl;
}

class server {
	SGE_NONCOPYABLE(server)
public:
	typedef void connect_fun (id_type);
	typedef void disconnect_fun (id_type,sge::string const &);
	typedef void data_fun (id_type,data_type const &);
	typedef boost::function<connect_fun> connect_function;
	typedef boost::function<disconnect_fun> disconnect_function;
	typedef boost::function<data_fun> data_function;

	server();
	void listen(port_type);
	void process();
	void queue(
		id_type,
		data_type const &);
	void queue(
		data_type const &);
	sge::signal::auto_connection register_connect(
		connect_function const &);
	sge::signal::auto_connection register_disconnect(
		disconnect_function const &);
	sge::signal::auto_connection register_data(
		data_function const &);

	~server();
private:
	sge::scoped_ptr<detail::server_impl> impl_;
};
}
}

#endif
