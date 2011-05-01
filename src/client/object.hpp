#ifndef SANGUIS_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_HPP_INCLUDED

#include "machine.hpp"
#include "config/settings/object.hpp"
#include "config/settings/saver.hpp"
#include "console/gfx.hpp"
#include "cursor/object.hpp"
#include "gui/object.hpp"
#include "../load/context.hpp"
#include "../net/port.hpp"
#include "../server/object_fwd.hpp"
#include "../main_object.hpp"
#include <sge/console/object.hpp>
#include <sge/font/text/drawer_3d.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/time/timer.hpp>
#include <sge/systems/instance.hpp>
#include <sge/window/instance_fwd.hpp>
#include <awl/mainloop/io_service_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/scoped_state_machine.hpp>
#include <boost/program_options/variables_map.hpp>


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
	int
	run();

	void
	register_handler();

	void
	loop_handler();

	void
	create_server(
		net::port
	);

	int
	quit_server();

	// declare the config stuff first, so they are destroyed last
	config::settings::object settings_;

	config::settings::saver saver_;

	sge::systems::instance const sys_;

	sge::font::metrics_ptr const font_metrics_;

	sge::font::text::drawer_3d font_drawer_;

	sge::console::object console_;

	client::console::gfx console_gfx_;

	sge::window::instance &window_;

	awl::mainloop::io_service_shared_ptr const io_service_;

	load::context resources_;

	client::cursor::object cursor_;

	client::gui::object gui_;

	client::machine machine_;

	sge::time::timer frame_timer_;

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
