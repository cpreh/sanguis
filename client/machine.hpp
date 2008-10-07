#ifndef SANGUIS_CLIENT_MACHINE_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_HPP_INCLUDED

#include "../messages/base.hpp"
#include "../net/client.hpp"
#include "../load/model/singleton.hpp"
#include "../tick_event.hpp"
#include "console_wrapper.hpp"

#include <sge/font/fwd.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_state_tracker.hpp> // TODO: remove me!
#include <sge/systems/instance_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <sge/console/console_gfx.hpp> // TODO: remove me!
#include <sge/console/stdlib.hpp>
#include <sge/renderer/device_fwd.hpp>

#include <boost/statechart/state_machine.hpp>

namespace sanguis
{
namespace client
{

struct start_state;

struct machine
	: public boost::statechart::state_machine<machine, start_state>
{
public:
	machine(
		sge::systems::instance &,
		sge::audio::pool_ptr,
		sge::font::font &,
		sge::input::key_state_tracker &,
		sge::con::console_gfx &,
		net::address_type const &,
		net::port_type);

	void connect();
	void send(messages::auto_ptr);
	void process_message(messages::auto_ptr);
	// callbacks
	void connect_callback();
	void disconnect_callback(net::string_type const &);
	void data_callback(net::data_type const &);

	net::address_type address() const;
	net::port_type port() const;
	net::client &net();

	bool process(tick_event const &);

	void dispatch();
	sge::renderer::device_ptr const renderer() const;
	sge::audio::player_ptr const audio_player() const;
	sge::audio::pool_ptr const sound_pool() const;
	sge::font::font &font();
	bool key_pressed(
		sge::input::key_code) const;
	console_wrapper &con_wrapper();
private:
	net::address_type address_;
	net::port_type port_;
	net::client net_;
	net::client::signal_connection s_conn,
	                               s_disconn,
	                               s_data;
	net::data_type in_buffer,
	               out_buffer;
	sge::systems::instance &sys;
	sge::audio::pool_ptr const sound_pool_;
	sge::font::font &font_;
	sge::input::key_state_tracker &ks;
	sge::con::console_gfx &con;
	sge::con::stdlib con_stdlib;
	console_wrapper con_wrapper_;
	load::model::connection model_connection;
};

}
}

#endif
