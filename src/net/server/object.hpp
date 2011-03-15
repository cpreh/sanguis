#ifndef SANGUIS_NET_SERVER_OBJECT_HPP_INCLUDED
#define SANGUIS_NET_SERVER_OBJECT_HPP_INCLUDED

#include "object_impl_fwd.hpp"
#include "connect_callback.hpp"
#include "data_callback.hpp"
#include "disconnect_callback.hpp"
#include "../data_buffer.hpp"
#include "../id.hpp"
#include "../port.hpp"
#include <awl/mainloop/io_service_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace net
{
namespace server
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		awl::mainloop::io_service &
	);	

	~object();

	void
	listen(
		net::port
	);

	void
	queue(
		net::id,
		net::data_buffer const &
	);

	fcppt::signal::auto_connection
	register_connect(
		server::connect_callback const &
	);

	fcppt::signal::auto_connection
	register_disconnect(
		server::disconnect_callback const &
	);

	fcppt::signal::auto_connection
	register_data(
		server::data_callback const &
	);
	
	void 
	stop();
private:
	fcppt::scoped_ptr<
		server::object_impl
	> impl_;
};

}
}
}

#endif
