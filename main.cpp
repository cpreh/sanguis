// own
#include "server/machine.hpp"
#include "client/machine.hpp"
#include "client/states/menu.hpp"
#include "client/message_event.hpp"
#include "server/states/running.hpp"
#include "server/states/unpaused.hpp"
#include "server/message_event.hpp"
#include "load/context.hpp"
#include "tick_event.hpp"
#include "media_path.hpp"
#include "resolution.hpp"
#include "log.hpp"
#include "log_switcher.hpp"
#include "log_context.hpp"

// sge
#include <sge/console/object.hpp>
#include <sge/console/gfx.hpp>
#include <sge/console/sprite_parameters.hpp>
#include <sge/console/sprite_object.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/font/system.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/drawer_3d.hpp>
#include <sge/font/object.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/device.hpp>
#include <sge/collision/system.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/colors.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/pool.hpp>
#include <sge/time/second.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/config/media_path.hpp>
#include <sge/log/global_context.hpp>

#include <fcppt/filesystem/exists.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/global.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/activate_levels.hpp>
#include <fcppt/log/level_from_string.hpp>
#include <fcppt/log/make_location.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/iconv.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/exception.hpp>

// boost
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/program_options.hpp>

// c++
#include <exception>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

// c
#include <cstdlib>

int
main(
	int argc,
	char *argv[]
)
try
{
	boost::program_options::options_description const desc(
		sanguis::args::options()
	);

	sanguis::log_switcher 
		sge_log(
			boost::phoenix::ref(
				desc
			),
			FCPPT_TEXT("sge"),
			sge::log::global_context()
		),
		sanguis_log(
			boost::phoenix::ref(
				desc
			),
			FCPPT_TEXT("sanguis"),
			sanguis::log_context()
		);
	
	boost::program_options::variables_map const vm(
		sanguis::args::parse(
			argc,
			argv,
			desc
		)
	);

	if (vm.count("help"))
	{
		std::cout << desc << '\n';
		return EXIT_SUCCESS;
	}

	// TODO: remove this global variable!
	/*sanguis::resolution(
		sge::renderer::screen_size(
			screen_width,
			screen_height
		)
	);*/

	fcppt::log::activate_levels(
		fcppt::log::global(),
		fcppt::log::level_from_string(
			fcppt::iconv(log_level)
		)
	);

	fcppt::log::activate_levels(
		sanguis::log(),
		fcppt::log::level_from_string(
			fcppt::iconv(log_level)
		)
	);

	sge::systems::instance sys(
		args::sge_options(
			vm
		)
	);
	// has to be done after the plugins are loaded
	sge_log.apply(
		vm
	);

	sanguis_log.apply(
		vm
	);

	/*
	sanguis::load::context resources(
		sys.image_loader(),
		sys.renderer(),
		audio_loader,
		sys.audio_player(),
		sound_pool
	);
	*/

	typedef fcppt::scoped_ptr<
		main_object
	> main_object_scoped_ptr;

	main_object_scoped_ptr obj(
		sanguis::args::serveronly(
			vm
		)
		?
			server::create(
				sys,
				vm,
				0 // no loader
			)
		:
			client::create(
				sys,
				vm
			)
		);
	
	return obj->run();
	
/*
	sge::time::timer frame_timer(
		sge::time::second(1)
	);

	bool running = true;
	while (running)
	{
		sanguis::tick_event t(static_cast<sanguis::time_type>(frame_timer.reset()));

		// get and send messages
		if(server)
			server->process(t);
		running = client.process(t);
	}
*/
}
catch (fcppt::exception const &e)
{
	fcppt::io::cerr
		<< FCPPT_TEXT("caught fcppt exception: ")
		<< e.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch (std::exception const &e)
{
	std::cerr
		<< "caught standard exception: "
		<< e.what()
		<< '\n';

	return EXIT_FAILURE;
}
