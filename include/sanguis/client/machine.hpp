#ifndef SANGUIS_CLIENT_MACHINE_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_HPP_INCLUDED

#include <sanguis/client/machine_fwd.hpp>
#include <sanguis/client/cursor/object_fwd.hpp>
#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sanguis/client/gui/object_fwd.hpp>
#include <sanguis/client/states/menu_fwd.hpp>
#include <sanguis/client/server_callback.hpp>
#include <sanguis/load/context_fwd.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/io_service_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/console/gfx_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <alda/net/host.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/object_fwd.hpp>
#include <alda/net/client/object.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>
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
		sanguis::client::machine,
		sanguis::client::states::menu
	>
{
	FCPPT_NONCOPYABLE(
		machine
	);
public:
	machine(
		sanguis::client::config::settings::object &,
		sanguis::client::gui::object &,
		sanguis::client::server_callback const &,
		sanguis::load::context const &,
		sge::window::system &,
		sge::font::object &,
		sge::console::gfx &,
		sge::input::keyboard::device &,
		sanguis::client::cursor::object &,
		sge::renderer::device::ffp &,
		sge::charconv::system &,
		sge::image2d::system &,
		sanguis::io_service &,
		sge::viewport::manager &
	);

	~machine();

	void
	quickstart(
		alda::net::port
	);

	void
	connect(
		alda::net::host const &,
		alda::net::port
	);

	void
	disconnect();

	void
	send(
		sanguis::messages::base const &
	);

	bool
	process(
		sanguis::duration const &
	);

	void
	draw();

	void
	quit();

	sanguis::client::config::settings::object &
	settings();

	sge::renderer::device::ffp &
	renderer() const;

	sge::charconv::system &
	charconv_system() const;

	sge::image2d::system &
	image_loader() const;

	sge::input::keyboard::device &
	keyboard() const;

	sge::font::object &
	font_object() const;

	sge::console::gfx &
	console_gfx();

	sanguis::load::context const &
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
		alda::net::buffer::circular_receive::object &
	);

	sanguis::client::config::settings::object &settings_;

	sanguis::client::gui::object &gui_;

	sanguis::load::context const &resources_;

	sge::input::keyboard::device &keyboard_;

	sge::renderer::device::ffp &renderer_;

	sge::charconv::system &charconv_system_;

	sge::image2d::system &image_loader_;

	sge::viewport::manager &viewport_manager_;

	alda::net::client::object net_;

	fcppt::signal::scoped_connection const
		s_conn_,
		s_disconn_,
		s_data_;

	sge::window::system &window_system_;

	sge::font::object &font_object_;

	sge::console::gfx &console_gfx_;

	sanguis::client::server_callback const server_callback_;

	sanguis::client::cursor::object &cursor_;
};

}
}

#endif
