#ifndef SANGUIS_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_HPP_INCLUDED

#include <sanguis/client/machine.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/config/settings/saver.hpp>
#include <sanguis/client/console/gfx.hpp>
#include <sanguis/client/cursor/object.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sanguis/load/context.hpp>
#include <sanguis/net/port.hpp>
#include <sanguis/server/object_fwd.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/main_object.hpp>
#include <sanguis/timer.hpp>
#include <sge/console/object.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/metrics_scoped_ptr.hpp>
#include <sge/systems/instance.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
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
	public main_object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit object(
		boost::program_options::variables_map const &
	);

	~object();
private:
	awl::main::exit_code const
	run();

	void
	register_handler();

	void
	loop_handler();

	void
	create_server(
		net::port
	);

	awl::main::exit_code const
	quit_server();

	// declare the config stuff first, so they are destroyed last
	config::settings::object settings_;

	config::settings::saver saver_;

	sanguis::io_service io_service_;

	sge::systems::instance const sys_;

	sge::font::metrics_scoped_ptr const font_metrics_;

	sge::font::text::drawer_3d font_drawer_;

	sge::console::object console_;

	client::console::gfx console_gfx_;

	load::context resources_;

	client::cursor::object cursor_;

	client::gui::object gui_;

	client::machine machine_;

	sanguis::timer frame_timer_;

	fcppt::scoped_ptr<
		server::object
	> server_;

	typedef fcppt::scoped_state_machine<
		client::machine
	> scoped_machine;

	scoped_machine scoped_machine_;
};

}
}

#endif
