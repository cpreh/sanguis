#ifndef SANGUIS_CLIENT_MACHINE_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_HPP_INCLUDED

#include "states/menu_fwd.hpp"
#include "cursor/object_fwd.hpp"
#include "config/settings/object_fwd.hpp"
#include "events/tick_fwd.hpp"
#include "gui/object_fwd.hpp"
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

#include <sge/audio/player_ptr.hpp>
#include <sge/audio/pool_fwd.hpp>
#include <sge/console/gfx_fwd.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/font/text/drawer_fwd.hpp>
#include <sge/input/keyboard/device_ptr.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <sge/renderer/device_ptr.hpp>

#include <awl/mainloop/io_service_fwd.hpp>

#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		machine
	);
public:
	machine(
		config::settings::object &,
		client::gui::object &,
		server_callback const &,
		load::context const &,
		sge::audio::pool &,
		sge::font::metrics_ptr,
		sge::font::text::drawer &,
		sge::console::gfx &,
		sge::input::keyboard::device_ptr,
		client::cursor::object &,
		sge::renderer::device_ptr,
		sge::image2d::multi_loader &,
		sge::audio::player_ptr,
		awl::mainloop::io_service &
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
		events::tick const &
	);

	void
	quit();

	config::settings::object &
	settings();

	sge::renderer::device_ptr const
	renderer() const;

	sge::image2d::multi_loader &
	image_loader() const;

	sge::input::keyboard::device_ptr const
	keyboard() const;

	sge::audio::player_ptr const
	audio_player() const;

	sge::audio::pool &
	sound_pool();

	sge::font::metrics_ptr const
	font_metrics() const;

	sge::font::text::drawer &
	font_drawer() const;

	sanguis::client::console &
	console();
	
	load::context const &
	resources() const;

	sanguis::client::cursor::object &
	cursor();

	sanguis::client::cursor::object const &
	cursor() const;

	sanguis::client::gui::object &
	gui() const;
private:
	config::settings::object &settings_;

	client::gui::object &gui_;

	load::context const &resources_;

	sge::input::keyboard::device_ptr const keyboard_;

	sge::renderer::device_ptr const renderer_;

	sge::image2d::multi_loader &image_loader_;

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

	sge::font::metrics_ptr const font_metrics_;

	sge::font::text::drawer &font_drawer_;

	sge::console::gfx &console_gfx_;
	
	sanguis::client::console console_;

	bool running_;

	server_callback const server_callback_;

	screenshot screenshot_;

	sanguis::client::cursor::object &cursor_;
};

}
}

#endif
