#ifndef SANGUIS_CLIENT_MACHINE_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_HPP_INCLUDED

#include "states/menu_fwd.hpp"
#include "cursor/object_ptr.hpp"
#include "cursor/const_object_ptr.hpp"
#include "config/settings/object_fwd.hpp"
#include "highscore/name_container.hpp"
#include "highscore/score_type.hpp"
#include "states/menu_fwd.hpp"
#include "console.hpp"
#include "screenshot.hpp"
#include "server_callback.hpp"
#include "../load/context_fwd.hpp"
#include "../messages/auto_ptr.hpp"
#include "../net/client.hpp"
#include "../net/data_type.hpp"
#include "../net/hostname_type.hpp"
#include "../net/port_type.hpp"
#include "../tick_event_fwd.hpp"

#include <sge/audio/player_ptr.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <sge/console/gfx_fwd.hpp>
#include <sge/console/stdlib.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/system_ptr.hpp>
#include <sge/input/key_code.hpp>
#include <sge/input/key_state_tracker_fwd.hpp>
#include <sge/input/system_ptr.hpp>
#include <sge/image/multi_loader_fwd.hpp>
#include <sge/renderer/device_ptr.hpp>

#include <fcppt/container/raw_vector_decl.hpp>

#include <boost/statechart/state_machine.hpp>

namespace sanguis
{
namespace client
{

class machine
:
	public boost::statechart::state_machine<
		machine,
		states::menu
	>
{
public:
	machine(
		config::settings::object &,
		server_callback const &,
		load::context const &,
		sge::audio::pool &,
		sge::font::object &,
		sge::input::key_state_tracker &,
		sge::console::gfx &,
		sge::input::system_ptr,
		sge::renderer::device_ptr,
		sge::image::multi_loader &,
		sge::font::system_ptr,
		sge::audio::player_ptr
	);

	~machine();

	void
	start_server();

	void
	connect(
		net::hostname_type const &,
		net::port_type
	);

	void
	cancel_connect();
	
	void
	send(
		messages::auto_ptr
	);
	
	void
	process_message(
		messages::auto_ptr
	);
	// callbacks
	
	void
	connect_callback();
	
	void
	disconnect_callback(
		fcppt::string const &
	);
	
	void
	data_callback(
		net::data_type const &
	);

	net::client &
	net();

	bool
	process(
		tick_event const &
	);

	void
	quit();

	void
	dispatch();

	config::settings::object &
	settings();

	sge::renderer::device_ptr const
	renderer() const;

	sge::image::multi_loader &
	image_loader() const;

	sge::font::system_ptr const
	font_system() const;

	sge::input::system_ptr const
	input_system() const;

	sge::audio::player_ptr const
	audio_player() const;

	sge::audio::pool &
	sound_pool();

	sge::font::object &
	font();

	bool
	key_pressed(
		sge::input::key_code
	) const;
	
	sanguis::client::console &
	console();
	
	load::context const &
	resources() const;

	sanguis::client::cursor::object_ptr const
	cursor();

	sanguis::client::cursor::const_object_ptr const
	cursor() const;

	// FIXME: this is so ugly
	client::highscore::name_container const &
	gameover_names() const;

	client::highscore::name_container &
	gameover_names();

	client::highscore::score_type
	gameover_score();

	void
	gameover_score(
		client::highscore::score_type
	);
private:
	config::settings::object &settings_;

	load::context const &resources_;

	sge::input::system_ptr const input_system_;

	sge::renderer::device_ptr const renderer_;

	sge::image::multi_loader &image_loader_;

	sge::font::system_ptr const font_system_;

	sge::audio::player_ptr const audio_player_;

	net::client net_;

	fcppt::signal::auto_connection
		s_conn,
		s_disconn,
		s_data;

	net::data_type
		in_buffer,
		out_buffer;

	sge::audio::pool &sound_pool_;

	sge::font::object &font_;

	sge::input::key_state_tracker &ks;

	sge::console::gfx &console_gfx_;
	
	sge::console::stdlib console_stdlib;

	sanguis::client::console console_;

	bool running_;

	server_callback const server_callback_;

	screenshot screenshot_;

	sanguis::client::cursor::object_ptr const cursor_;

	client::highscore::name_container gameover_names_;

	client::highscore::score_type gameover_score_;
};

}
}

#endif
