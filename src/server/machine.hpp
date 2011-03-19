#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include "machine_fwd.hpp"
#include "states/running_fwd.hpp"
#include "../load/context_base_fwd.hpp"
#include "../messages/auto_ptr.hpp"
#include "../net/server/object.hpp"
#include "../net/data_buffer.hpp"
#include "../net/id.hpp"
#include "../net/port.hpp"
#include "../net/receive_buffer_fwd.hpp"
#include <sge/collision/system_ptr.hpp>
#include <sge/time/timer.hpp>
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <awl/mainloop/io_service_fwd.hpp>
#include <boost/statechart/state_machine.hpp>
#include <set>

namespace sanguis
{
namespace server
{

struct machine
:
	public boost::statechart::state_machine<
		machine,
		states::running
	>
{
	FCPPT_NONCOPYABLE(
		machine
	);
public:
	machine(
		load::context_base const &,
		sge::collision::system_ptr,
		net::port,
		awl::mainloop::io_service &
	);

	~machine();

	void
	process_message(
		net::id,
		messages::auto_ptr
	);

	void
	connect_callback(
		net::id
	);

	void
	disconnect_callback(
		net::id,
		fcppt::string const &
	);

	void
	data_callback(
		net::id,
		net::receive_buffer &
	);

	void
	send_to_all(
		messages::auto_ptr
	);

	void 
	stop();

	void
	listen();

	load::context_base const &
	resources() const;

	sge::collision::system_ptr const
	collision_system() const;

	void
	send_unicast(
		net::id,
		messages::auto_ptr
	);
private:
	void
	timer_callback();

	typedef std::set<
		net::id
	> client_set;

	load::context_base const &resources_;

	net::port const port_;

	net::server::object net_;

	sge::time::timer frame_timer_;

	net::data_buffer temp_buffer_;

	fcppt::signal::scoped_connection const
		s_conn_,
		s_disconn_,
		s_data_,
		s_timer_;

	client_set clients_;

	sge::collision::system_ptr const collision_;
};

}
}

#endif
