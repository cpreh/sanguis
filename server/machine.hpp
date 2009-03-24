#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include "states/start_fwd.hpp"
#include "../load/context_fwd.hpp"
#include "../messages/base.hpp"
#include "../net/server.hpp"
#include "../tick_event.hpp"
#include "message_event.hpp"
#include <sge/console/gfx_fwd.hpp>
#include <sge/collision/world_fwd.hpp>
#include <sge/string.hpp>
#include <boost/statechart/state_machine.hpp>
#include <map>

namespace sanguis
{
namespace server
{

struct client_data
{
	net::data_type in_buffer;
	net::data_type out_buffer;
};

struct machine
	: public boost::statechart::state_machine<machine, states::start>
{
public:
	machine(
		load::context const &,
		sge::collision::world_ptr,
		sge::console::gfx &,
		::net::port_type);
	void process(tick_event const &);
	void process_message(
		::net::id_type,
		messages::auto_ptr);

	void connect_callback(
		::net::id_type);
	void disconnect_callback(
		::net::id_type,
		::net::string_type const &);
	void data_callback(
		::net::id_type,
		::net::data_type const &);

	void send(
		messages::auto_ptr m);

	void send(
		messages::auto_ptr,
		::net::id_type dest);

	void console_print(
		sge::string const &);
	::net::port_type port() const;
	::net::server &net();
	void listen();

	load::context const &
	resources() const;

	sge::collision::world_ptr const collision();
private:
	typedef std::map<
		::net::id_type,
		client_data
	> client_map;

	load::context const &resources_;
	::net::port_type port_;
	::net::server net_;
	::net::server::signal_connection
		s_conn,
		s_disconn,
		s_data;
	client_map clients;
	sge::collision::world_ptr collision_;
	sge::console::gfx &con;
};

}
}

#endif
