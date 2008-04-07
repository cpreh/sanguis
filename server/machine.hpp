#ifndef SANGUIS_SERVER_MACHINE_HPP_INCLUDED
#define SANGUIS_SERVER_MACHINE_HPP_INCLUDED

#include "../messages/base.hpp"
#include "../net/server.hpp"
#include "../load/model/singleton.hpp"
#include "../load/resource_factory.hpp"
#include "../tick_event.hpp"
#include "message_event.hpp"

#include <sge/systems_fwd.hpp>

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

struct start_state;
struct machine
	: public boost::statechart::state_machine<machine, start_state>
{
	public:
	machine(
		sge::systems &,
		net::port_type);
	void process(const tick_event &);
	void process_message(const net::id_type,const message_ptr);

	void connect_callback(const net::id_type);
	void disconnect_callback(const net::id_type,const net::string_type &);
	void data_callback(const net::id_type,const net::data_type &);

	void send(messages::base *const m);
	net::port_type port() const { return port_; }
	net::server &net() { return net_; }
	void listen();

	private:
	typedef std::map<net::id_type,client_data> client_map;

	net::port_type port_;
	net::server net_;
	net::server::signal_connection s_conn,
	                               s_disconn,
	                               s_data;
	load::resource::connection resource_connection;
	load::model::connection model_connection;
	client_map clients;
};

}
}

#endif
