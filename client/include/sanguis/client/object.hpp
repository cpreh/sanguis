#ifndef SANGUIS_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_HPP_INCLUDED

#include <sanguis/io_service.hpp>
#include <sanguis/timer.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/object_base.hpp>
#include <sanguis/client/server_fwd.hpp>
#include <sanguis/client/systems_fwd.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/config/settings/saver.hpp>
#include <sanguis/client/console/gfx.hpp>
#include <sanguis/client/load/context.hpp>
#include <sge/console/object.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/font/object_scoped_ptr.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{

class object
:
	public sanguis::client::object_base
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		boost::program_options::variables_map const &
	);

	~object()
	override;
private:
	awl::main::exit_code const
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

	awl::main::exit_code const
	quit_server();

	// declare the config stuff first, so they are destroyed last
	sanguis::client::config::settings::object settings_;

	sanguis::client::config::settings::saver saver_;

	sanguis::io_service io_service_;

	typedef fcppt::scoped_ptr<
		sanguis::client::systems
	> systems_scoped_ptr;

	systems_scoped_ptr const sys_;

	sge::renderer::device::core &renderer_;

	sge::font::object_scoped_ptr const font_object_;

	sge::console::object console_;

	sanguis::client::console::gfx console_gfx_;

	sanguis::client::load::context resources_;

	sanguis::client::machine machine_;

	sanguis::timer frame_timer_;

	fcppt::scoped_ptr<
		sanguis::client::server
	> server_;

	typedef fcppt::scoped_state_machine<
		sanguis::client::machine
	> scoped_machine;

	scoped_machine scoped_machine_;
};

}
}

#endif