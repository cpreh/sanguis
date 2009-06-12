#ifndef SANGUIS_CLIENT_MACHINE_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_HPP_INCLUDED

#include "states/fwd.hpp"
#include "screenshot.hpp"
#include "cursor/object_ptr.hpp"
#include "cursor/const_object_ptr.hpp"
#include "server_callback.hpp"
#include "console_wrapper.hpp"
#include "../load/context_fwd.hpp"
#include "../messages/auto_ptr.hpp"
#include "../net/client.hpp"
#include "../tick_event_fwd.hpp"
#include "highscore/name_container.hpp"
#include "highscore/score_type.hpp"

#include <sge/font/object_fwd.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/key_state_tracker_fwd.hpp>
#include <sge/systems/instance_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/stdlib.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/container/raw_vector_decl.hpp>

#include <boost/statechart/state_machine.hpp>

namespace sanguis
{
namespace client
{
struct machine
	: public boost::statechart::state_machine<machine, states::menu>
{
public:
	machine(
		server_callback const &,
		load::context const &,
		sge::systems::instance &,
		sge::audio::pool &,
		sge::font::object &,
		sge::input::key_state_tracker &,
		sge::console::gfx &);

	void start_server();
	void connect(
		net::hostname_type const &,
		net::port_type);

	void cancel_connect();
	void send(messages::auto_ptr);
	void process_message(messages::auto_ptr);
	// callbacks
	void connect_callback();
	void disconnect_callback(sge::string const &);
	void data_callback(net::data_type const &);

	net::client &net();

	bool process(tick_event const &);

	void quit();
	void dispatch();
	sge::renderer::device_ptr const renderer() const;
	sge::systems::instance &sys() const;
	sge::audio::player_ptr const audio_player() const;
	sge::audio::pool &sound_pool();
	sge::font::object &font();
	bool key_pressed(
		sge::input::key_code) const;
	
	sanguis::client::console_wrapper &
	console_wrapper();
	
	load::context const &
	resources() const;

	sanguis::client::cursor::object_ptr const cursor();
	sanguis::client::cursor::const_object_ptr const cursor() const;

	// FIXME: this is so ugly
	client::highscore::name_container const &gameover_names() const;
	client::highscore::name_container &gameover_names();
	client::highscore::score_type gameover_score();
	void gameover_score(
		client::highscore::score_type);
private:
	load::context const &resources_;
	net::client net_;
	sge::signal::auto_connection
		s_conn,
		s_disconn,
		s_data;
	net::data_type
		in_buffer,
		out_buffer;
	sge::systems::instance &sys_;
	sge::audio::pool &sound_pool_;
	sge::font::object &font_;
	sge::input::key_state_tracker &ks;
	sge::console::gfx &console;
	sge::console::stdlib console_stdlib;
	sanguis::client::console_wrapper console_wrapper_;
	bool running_;
	server_callback const server_callback_;
	screenshot screenshot_;
	sanguis::client::cursor::object_ptr const cursor_;
	client::highscore::name_container gameover_names_;
	client::highscore::score_type gameover_score_;
	//sge::sprite::system ss_;
	//sge::renderer::glsl::program_ptr shader_;
	//sge::renderer::glsl::uniform::variable_ptr shadervar_;
	//sge::renderer::texture_ptr target_;
	//sge::sprite::object target_sprite_;
};

}
}

#endif
