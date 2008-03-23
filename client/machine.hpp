#ifndef SANGUIS_CLIENT_MACHINE_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_HPP_INCLUDED

#include "../messages/base.hpp"
#include "../net/client.hpp"
#include "../draw/resource_factory.hpp"
#include "../tick_event.hpp"

#include <sge/font/font_metrics.hpp>
#include <sge/font/font_system.hpp>
#include <sge/font/font_drawer.hpp>
#include <sge/font/font.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/systems.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/no_fragmented_texture.hpp>
#include <sge/texture/manager.hpp>

#include <boost/statechart/state_machine.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

namespace sanguis
{
namespace client
{
struct start_state;
struct machine
	: public boost::statechart::state_machine<machine, start_state>
{
	private:
	net::address_type address_;
	net::port_type port_;
	net::client net_;
	net::client::signal_connection s_conn,s_disconn,s_data;
	net::data_type in_buffer,out_buffer;

	public:
	sge::systems &sys;
	sge::font &font;
	sge::key_state_tracker &ks;
	draw::resource::connection resource;

	machine(sge::systems &,sge::font &,sge::key_state_tracker &,const net::address_type &,const net::port_type);

	void connect();
	void push_back(messages::base *const);
	void process_message(const message_ptr);
	// callbacks
	void connect_callback();
	void disconnect_callback(const net::string_type &);
	void data_callback(const net::data_type &);

	net::address_type address() const { return address_; }
	net::port_type port() const { return port_; }
	net::client &net() { return net_; }

	bool process(const tick_event &);
};

}
}

#endif
