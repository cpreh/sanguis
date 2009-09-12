// own
#include "server/machine.hpp"
#include "client/machine.hpp"
#include "client/states/menu.hpp"
#include "client/message_event.hpp"
#include "server/states/running.hpp"
#include "server/states/unpaused.hpp"
#include "server/entities/entity.hpp"
#include "load/context.hpp"
#include "tick_event.hpp"
#include "media_path.hpp"
#include "resolution.hpp"
#include "log.hpp"

// sge
#include <sge/cerr.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/iconv.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/auto_ptr.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/console/object.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/log/level.hpp>
#include <sge/log/logger.hpp>
#include <sge/log/global.hpp>
#include <sge/log/level_string.hpp>
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
#include <sge/collision/system.hpp>
#include <sge/image/loader.hpp>
#include <sge/image/colors.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/pool.hpp>
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/input/key_state_tracker.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/config/media_path.hpp>
#include <sge/math/rect/basic_impl.hpp>

// boost
#include <boost/filesystem.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/program_options.hpp>

// c++
#include <exception>
#include <iostream>
#include <fstream>
#include <ostream>

// c
#include <cstdlib>

// FIXME: this should not be here!
namespace
{

typedef sge::scoped_ptr<
	sanguis::server::machine
> server_scoped_ptr;

void
create_server(
	server_scoped_ptr &server,
	sanguis::load::context const &resources,
	sge::collision::world_ptr const coll,
	sge::console::gfx &con,
	sanguis::net::port_type const host_port)
{
	server.reset(
		new sanguis::server::machine(
			resources,
			coll,
			con, 
			host_port
		)
	);
	
	server->initiate();
}

}

int main(int argc,char *argv[])
try
{
	namespace po = boost::program_options;
	po::options_description desc("allowed options");

	std::string log_level;
	unsigned screen_width, screen_height;

	desc.add_options()
		("help",
			"produce help message")
		("log",
			po::value<std::string>(&log_level)->default_value(std::string("debug")),
			"sets the maximum logging level (one of debug, info, warning, error, fatal in that order)")
		("width",
			po::value<unsigned>(&screen_width)->default_value(1024),
			"sets the display width")
		("height",
			po::value<unsigned>(&screen_height)->default_value(768));
	
	po::variables_map vm;
	po::store(po::parse_command_line(argc,argv,desc),vm);
	if (boost::filesystem::exists(SGE_TEXT("config")))
	{
		// NOTE: this has to be a std::ifstream since boost::po only handels those cases
		std::ifstream config_file("config");
		// highly unlikely to happen
		if (!config_file.is_open())
		{
			std::cerr << "couldn't open config file\n";
			return EXIT_FAILURE;
		}
		po::store(po::parse_config_file(config_file,desc),vm);
	}
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << desc << '\n';
		return EXIT_SUCCESS;
	}

	sanguis::resolution(
		sge::renderer::screen_size(
			screen_width,
			screen_height));

	sge::log::global().activate_hierarchy(
		sge::log::level_from_string(
			sge::iconv(log_level)));

	sanguis::log().activate_hierarchy(
		sge::log::level_from_string(
			sge::iconv(log_level)));

	sge::systems::instance sys(
		sge::systems::list()
		(sge::window::parameters(
			SGE_TEXT("sanguis")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sanguis::resolution(),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed,
			sge::renderer::vsync::on))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::image)
		(sge::systems::parameterless::audio_player)
		(sge::systems::named(
			sge::systems::parameterless::collision_system,
			SGE_TEXT("cell")
		))
		(sge::systems::parameterless::font));

	// input stuff
	sge::input::key_state_tracker ks(sys.input_system());

	// font stuff
	sge::font::metrics_ptr const metrics(
		sys.font_system()->create_font(
			sge::config::media_path() / SGE_TEXT("fonts") / SGE_TEXT("default.ttf"),
			static_cast<sge::font::size_type>(15)
		)
	);

	sge::font::drawer_ptr const drawer(
		sge::make_shared_ptr<sge::font::drawer_3d>(
			sys.renderer(),
			sge::image::colors::white()
		)
	);
	
	sge::font::object font(
		metrics,
		drawer
	);

	sge::texture::manager texman(
		sys.renderer(),
		sge::texture::default_creator<sge::texture::no_fragmented>(
			sys.renderer(),
			sge::image::color::format::rgba8, // TODO: what do we want to use here?
			sge::renderer::filter::linear
		)
	);

	sge::console::object console(SGE_TEXT('/'));

	sge::console::gfx console_gfx(
		console,
		sys.renderer(),
		sge::image::colors::white(),
		metrics,
		sys.input_system(),
		sge::sprite::object(
			sge::sprite::parameters()
			.texture(
				sge::texture::add_image(
					texman,
					sys.image_loader()->load(
						sanguis::media_path() / SGE_TEXT("console_back.png")
					)
				)
			)
			.size(
				sge::sprite::dim(
					sys.renderer()->screen_size().w(),
					static_cast<sge::sprite::unit>(
						sys.renderer()->screen_size().h() / 2
					)
				)
			)
		)
	);
	
	sge::collision::unit const additional_size(
		500
	);

	sge::collision::world_ptr const world = 
		sys.collision_system()->create_world(
			sge::collision::rect(
				-additional_size,
				-additional_size,
				static_cast<sge::collision::unit>(
					sanguis::resolution().w()
				)+ additional_size,
				static_cast<sge::collision::unit>(
					sanguis::resolution().h()
				) + additional_size
			)
		);
	
	sge::audio::multi_loader 
		audio_loader(
			sys.plugin_manager());
	sge::audio::pool sound_pool;

	sanguis::load::context resources(
		sys.image_loader(),
		sys.renderer(),
		audio_loader,
		sys.audio_player(),
		sound_pool);
	
	server_scoped_ptr server;

	// construct and initialize statemachine
	sanguis::client::machine client(
		boost::phoenix::bind(
			&create_server,
			boost::phoenix::ref(server),
			boost::phoenix::ref(resources),
			world,
			boost::phoenix::ref(console_gfx),
			boost::phoenix::arg_names::_1
		),
		resources,
		sys,
		sound_pool,
		font,
		ks,
		console_gfx
	);

	// this should construct, among others, the renderer
	client.initiate();

	sge::time::timer frame_timer(
		sge::time::second(1));

	bool running = true;
	while (running)
	{
		sanguis::tick_event t(static_cast<sanguis::time_type>(frame_timer.reset()));

		// get and send messages
		if(server)
			server->process(t);
		running = client.process(t);
	}
} catch (sge::exception const &e) {
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.string() << SGE_TEXT('\n');
	return EXIT_FAILURE;
} catch (std::exception const &e) {
	std::cerr << "caught standard exception: " << e.what() << '\n';
	return EXIT_FAILURE;
}
