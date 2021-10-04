#ifndef SANGUIS_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_HPP_INCLUDED

#include <sanguis/clock.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/client/cursor.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/object_base.hpp>
#include <sanguis/client/server_fwd.hpp>
#include <sanguis/client/systems_fwd.hpp>
#include <sanguis/client/args/result_fwd.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/config/settings/saver.hpp>
#include <sanguis/client/console/gfx.hpp>
#include <sanguis/client/load/context.hpp>
#include <alda/net/port.hpp>
#include <sge/console/object.hpp>
#include <sge/font/added_unique_ptr.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/gui/style/base_unique_ptr.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/timer/absolute_decl.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sanguis::client
{

class object
:
	public sanguis::client::object_base
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		fcppt::log::context_reference,
		sanguis::client::args::result const &
	);

	~object()
	override;
private:
	[[nodiscard]]
	awl::main::exit_code
	run()
	override;

	void
	register_handler();

	void
	loop_handler();

	void
	create_server(
		alda::net::port
	);

	[[nodiscard]]
	awl::main::exit_code
	quit_server();

	fcppt::log::context_reference const log_context_;

	fcppt::log::object log_;

	// declare the config stuff first, so they are destroyed last
	sanguis::client::config::settings::object settings_;

	sanguis::client::config::settings::saver saver_;

	sanguis::io_service io_service_;

	using
	systems_unique_ptr
	=
	fcppt::unique_ptr<
		sanguis::client::systems
	>;

	systems_unique_ptr const sys_;

	sge::renderer::device::core_ref const renderer_;

	sge::font::added_unique_ptr const added_font_;

	sge::font::object_unique_ptr const font_object_;

	sanguis::client::load::context resources_;

	sge::gui::style::base_unique_ptr const gui_style_;

	sge::console::object console_;

	sanguis::client::console::gfx console_gfx_;

	sanguis::client::cursor cursor_;

	sanguis::client::machine machine_;

	using
	frame_timer
	=
	sge::timer::absolute<
		sanguis::clock
	>;

	frame_timer frame_timer_;

	using
	server_unique_ptr
	=
	fcppt::unique_ptr<
		sanguis::client::server
	>;

	using
	optional_server_unique_ptr
	=
	fcppt::optional::object<
		server_unique_ptr
	>;

	optional_server_unique_ptr server_;

	using
	scoped_machine
	=
	fcppt::scoped_state_machine<
		sanguis::client::machine
	>;

	scoped_machine scoped_machine_;
};

}

#endif
