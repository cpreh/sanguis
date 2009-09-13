#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include "states/running_fwd.hpp"
#include "client_data.hpp"
#include "send_callback.hpp"
#include "../load/context_fwd.hpp"
#include "../messages/base.hpp"
#include "../net/server.hpp"
#include "../tick_event.hpp"
#include "message_event.hpp"
#include <sge/console/gfx_fwd.hpp>
#include <sge/collision/system_fwd.hpp>
#include <sge/container/map_decl.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/string.hpp>
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
		load::context const &,
		sge::collision::system_ptr,
		sge::console::gfx &,
		net::port_type
	);

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
		sge::string const &
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
	listen();

	load::context const &
	resources() const;

	sge::collision::system_ptr const
	collision_system() const;

	void
	send_unicast(
		messages::auto_ptr,
		net::id_type
	);
private:
	typedef sge::container::map<
		std::map,
		net::id_type,
		client_data
	> client_map;

	net::port_type const port_;

	net::server net_;

	sge::signal::scoped_connection const
		s_conn,
		s_disconn,
		s_data;

	client_map clients;
};

}
}

#endif
