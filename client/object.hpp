#ifndef SANGUIS_CLIENT_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_OBJECT_HPP_INCLUDED

#include "machine.hpp"
#include "config/settings/object.hpp"
#include "../load/context.hpp"
#include "../net/port_type.hpp"
#include "../server/object_fwd.hpp"
#include "../main_object.hpp"

#include <sge/audio/multi_loader.hpp>
#include <sge/audio/pool.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/object.hpp>
#include <sge/font/drawer_ptr.hpp>
#include <sge/font/metrics_ptr.hpp>
#include <sge/font/object.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/systems/instance_fwd.hpp>
#include <sge/texture/manager.hpp>

#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

#include <boost/program_options/variables_map.hpp>

namespace sanguis
{
namespace client
{

class object
:
	public main_object
{
	FCPPT_NONCOPYABLE(object)
public:
	explicit object(
		sge::systems::instance &,
		boost::program_options::variables_map const &
	);

	~object();
private:
	int
	run();

	void
	create_server(
		net::port_type
	);

	int
	do_quit();

	int
	quit_server();

	sge::systems::instance &sys_;

	sge::input::key_state_tracker key_state_tracker_;
	
	sge::font::metrics_ptr const font_metrics_;

	sge::font::drawer_ptr const font_drawer_;

	sge::font::object font_;

	sge::texture::manager texture_manager_;

	sge::console::object console_;

	sge::console::gfx console_gfx_;

	sge::audio::multi_loader audio_loader_;

	sge::audio::pool sound_pool_;

	load::context resources_;

	config::settings::object settings_;

	client::machine machine_;

	fcppt::scoped_ptr<
		server::object
	> server_;
};

}
}

#endif
