#ifndef SANGUIS_CLIENT_MACHINE_HPP_INCLUDED
#define SANGUIS_CLIENT_MACHINE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/io_service_ref.hpp>
#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/cursor_ref.hpp>
#include <sanguis/client/machine_fwd.hpp>
#include <sanguis/client/server_callback.hpp>
#include <sanguis/client/args/result_fwd.hpp>
#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sanguis/client/config/settings/object_ref.hpp>
#include <sanguis/client/load/context_cref.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/states/menu_fwd.hpp>
#include <sanguis/messages/client/base_fwd.hpp>
#include <alda/net/host.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>
#include <alda/net/client/object.hpp>
#include <sge/console/gfx/object_fwd.hpp>
#include <sge/console/gfx/object_ref.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <sge/window/system_ref.hpp>
#include <awl/event/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
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
	FCPPT_NONMOVABLE(
		machine
	);
public:
	machine(
		fcppt::log::context_reference,
		sanguis::client::config::settings::object_ref,
		sanguis::client::args::result &&,
		sanguis::client::server_callback &&,
		sanguis::client::load::context_cref,
		sge::gui::style::const_reference,
		sge::window::system_ref,
		sge::font::object_ref,
		sge::console::gfx::object_ref,
		sge::renderer::device::ffp_ref,
		sanguis::io_service_ref,
		sge::viewport::manager_ref,
		sanguis::client::cursor_ref
	);

	~machine()
	override;

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
		sanguis::messages::client::base const &
	);

	[[nodiscard]]
	bool
	process(
		sanguis::duration const &
	);

	void
	quit();

	[[nodiscard]]
	sanguis::client::config::settings::object &
	settings();

	[[nodiscard]]
	sanguis::client::args::result const &
	options() const;

	[[nodiscard]]
	sge::gui::style::base const &
	gui_style() const;

	[[nodiscard]]
	sge::renderer::device::ffp &
	renderer() const;

	[[nodiscard]]
	sge::font::object &
	font_object() const;

	[[nodiscard]]
	sge::console::gfx::object &
	console_gfx();

	[[nodiscard]]
	sanguis::client::load::context const &
	resources() const;

	[[nodiscard]]
	sge::viewport::manager &
	viewport_manager() const;

	[[nodiscard]]
	sanguis::client::cursor &
	cursor_gfx() const;

	[[nodiscard]]
	fcppt::log::context_reference
	log_context() const;
private:
	void
	draw();

	void
	process_sge_event(
		awl::event::base const &
	);

	void
	connect_callback();

	void
	error_callback(
		fcppt::string const &,
		boost::system::error_code const &
	);

	void
	data_callback(
		alda::net::buffer::circular_receive::streambuf & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	fcppt::log::context_reference const log_context_;

	fcppt::log::object log_;

	sanguis::client::config::settings::object_ref const settings_;

	sanguis::client::args::result const options_;

	sanguis::client::load::context_cref const resources_;

	sge::gui::style::const_reference const gui_style_;

	sge::renderer::device::ffp_ref const renderer_;

	sge::viewport::manager_ref const viewport_manager_;

	alda::net::client::object net_;

	fcppt::signal::auto_connection const s_conn_;
	fcppt::signal::auto_connection const s_disconn_;
	fcppt::signal::auto_connection const s_data_;

	sge::window::system_ref const window_system_;

	sge::font::object_ref const font_object_;

	sge::console::gfx::object_ref const console_gfx_;

	sanguis::client::server_callback const server_callback_;

	sanguis::client::cursor_ref const cursor_gfx_;
};

}
}

#endif
