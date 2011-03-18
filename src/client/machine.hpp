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
#include "../net/client/object.hpp"
#include "../net/data_buffer.hpp"
#include "../net/hostname.hpp"
#include "../net/port.hpp"

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
#include <fcppt/string.hpp>

#include <boost/statechart/state_machine.hpp>
#include <boost/system/error_code.hpp>

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
	quickstart(
		net::port
	);

	void
	connect(
		net::hostname const &,
		net::port
	);

	void
	cancel_connect();
	
	void
	send(
		messages::auto_ptr
	);
	
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
	void
	connect_callback();
	
	void
	error_callback(
		fcppt::string const &,
		boost::system::error_code const &
	);
	
	void
	data_callback(
		net::data_buffer const &
	);

	config::settings::object &settings_;

	client::gui::object &gui_;

	load::context const &resources_;

	sge::input::keyboard::device_ptr const keyboard_;

	sge::renderer::device_ptr const renderer_;

	sge::image2d::multi_loader &image_loader_;

	sge::audio::player_ptr const audio_player_;

	net::client::object net_;

	fcppt::signal::auto_connection const
		s_conn_,
		s_disconn_,
		s_data_;

	net::data_buffer
		in_buffer_,
		out_buffer_;

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
