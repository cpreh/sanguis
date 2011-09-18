#ifndef SANGUIS_CLIENT_MACHINE_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_HPP_INCLUDED

#include <sanguis/client/machine_fwd.hpp>
#include <sanguis/client/cursor/object_fwd.hpp>
#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sanguis/client/gui/object_fwd.hpp>
#include <sanguis/client/states/menu_fwd.hpp>
#include <sanguis/client/server_callback.hpp>
#include <sanguis/load/context_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/net/client/object.hpp>
#include <sanguis/net/hostname.hpp>
#include <sanguis/net/port.hpp>
#include <sanguis/net/receive_buffer_fwd.hpp>
#include <sanguis/duration_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/console/gfx_fwd.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/text/drawer_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/image2d/multi_loader_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <awl/mainloop/io_service_fwd.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/system/error_code.hpp>
#include <fcppt/config/external_end.hpp>

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
		client::server_callback const &,
		load::context const &,
		sge::font::metrics &,
		sge::font::text::drawer &,
		sge::console::gfx &,
		sge::input::keyboard::device &,
		client::cursor::object &,
		sge::renderer::device &,
		sge::image2d::multi_loader &,
		sge::audio::player &,
		awl::mainloop::io_service &,
		sge::viewport::manager &
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
	disconnect();

	void
	send(
		messages::auto_ptr
	);

	bool
	process(
		sanguis::duration const &
	);

	void
	draw();

	void
	quit();

	config::settings::object &
	settings();

	sge::renderer::device &
	renderer() const;

	sge::image2d::multi_loader &
	image_loader() const;

	sge::input::keyboard::device &
	keyboard() const;

	sge::audio::player &
	audio_player() const;

	sge::font::metrics &
	font_metrics() const;

	sge::font::text::drawer &
	font_drawer() const;

	sge::console::gfx &
	console_gfx();

	load::context const &
	resources() const;

	sanguis::client::cursor::object &
	cursor();

	sanguis::client::cursor::object const &
	cursor() const;

	sanguis::client::gui::object &
	gui() const;

	sge::viewport::manager &
	viewport_manager() const;
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
		net::receive_buffer &
	);

	config::settings::object &settings_;

	client::gui::object &gui_;

	load::context const &resources_;

	sge::input::keyboard::device &keyboard_;

	sge::renderer::device &renderer_;

	sge::image2d::multi_loader &image_loader_;

	sge::audio::player &audio_player_;

	sge::viewport::manager &viewport_manager_;

	net::client::object net_;

	fcppt::signal::auto_connection const
		s_conn_,
		s_disconn_,
		s_data_;

	sge::font::metrics &font_metrics_;

	sge::font::text::drawer &font_drawer_;

	sge::console::gfx &console_gfx_;

	bool running_;

	client::server_callback const server_callback_;

	sanguis::client::cursor::object &cursor_;
};

}
}

#endif
