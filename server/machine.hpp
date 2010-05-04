#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include "states/running_fwd.hpp"
#include "client_data.hpp"
#include "../load/context_base_fwd.hpp"
#include "../messages/auto_ptr.hpp"
#include "../net/server.hpp"
#include "../net/id_type.hpp"
#include "../tick_event_fwd.hpp"
#include <sge/collision/system_ptr.hpp>
#include <fcppt/container/map_decl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/string.hpp>
#include <boost/statechart/state_machine.hpp>
#include <map>

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
public:
	machine(
		load::context_base const &,
		sge::collision::system_ptr,
		net::port_type
	);

	~machine();

	void
	process(
		tick_event const &
	);

	void
	process_message(
		net::id_type,
		messages::auto_ptr
	);

	void
	connect_callback(
		net::id_type
	);

	void
	disconnect_callback(
		net::id_type,
		fcppt::string const &
	);

	void
	data_callback(
		net::id_type,
		net::data_type const &
	);

	void
	send_to_all(
		messages::auto_ptr
	);

	net::port_type
	port() const;

	net::server &
	net();

	void 
	run();

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
		net::id_type,
		messages::auto_ptr
	);
private:
	typedef fcppt::container::map<
		std::map<
			net::id_type,
			client_data
		>
	> client_map;

	load::context_base const &resources_;

	net::port_type const port_;

	net::server net_;

	fcppt::signal::scoped_connection const
		s_conn,
		s_disconn,
		s_data;

	client_map clients_;

	sge::collision::system_ptr const collision_;
};

}
}

#endif
