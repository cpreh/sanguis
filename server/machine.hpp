#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include "../messages/base.hpp"
#include "../net/server.hpp"
#include "../load/model/singleton.hpp"
#include "../tick_event.hpp"
#include "message_event.hpp"

#include <sge/console/console_gfx.hpp>

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

namespace states
{
struct start;
}

struct machine
	: public boost::statechart::state_machine<machine, states::start>
{
public:
	machine(
		sge::con::console_gfx &,
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
private:
	typedef std::map<
		::net::id_type,
		client_data
	> client_map;

	::net::port_type port_;
	::net::server net_;
	::net::server::signal_connection
		s_conn,
		s_disconn,
		s_data;
	load::model::connection model_connection;
	client_map clients;
	sge::con::console_gfx &con;
};

}
}

#endif
