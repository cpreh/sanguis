// own
#include "server/machine.hpp"
#include "server/states/start.hpp"
#include "client/machine.hpp"
#include "client/start_state.hpp"
#include "load/resource/connection.hpp"
#include "tick_event.hpp"
#include "media_path.hpp"
#include "resolution.hpp"
#include "log.hpp"

// sge
#include <sge/iostream.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/iconv.hpp>
#include <sge/media.hpp>
#include <sge/console/console.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/log/level.hpp>
#include <sge/log/logger.hpp>
#include <sge/log/global.hpp>
#include <sge/log/level_string.hpp>
#include <sge/font/system.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/drawer_3d.hpp>
#include <sge/font/font.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/util.hpp>
#include <sge/image/loader.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/time/second.hpp>

// boost
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

// c++
#include <exception>
#include <iostream>
#include <fstream>
#include <ostream>

// c
#include <cstdlib>

int main(int argc,char *argv[])
try
{
	namespace po = boost::program_options;
	po::options_description desc("allowed options");

	net::address_type dest_server;
	net::port_type host_port,dest_port;
	std::string log_level;

	desc.add_options()
			("help",
				"produce help message")
			("dest-server",
				po::value<net::address_type>(&dest_server)->default_value("localhost"),
				"sets the server (ip/hostname) to connect to when hitting space")
			("dest-port",
				po::value<net::port_type>(&dest_port)->default_value(1337),
				"sets the server port to connect to")
			("host-port",
				po::value<net::port_type>(&host_port)->default_value(1337),
				"sets the port to listen to for games")
			("log",
				po::value<std::string>(&log_level)->default_value(std::string("debug")),
				"sets the maximum logging level (one of debug, info, warning, error, fatal in that order)");
	
	po::variables_map vm;
	po::store(po::parse_command_line(argc,argv,desc),vm);
	if (boost::filesystem::exists("config"))
	{
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

	sge::log::global().activate_hierarchy(
		sge::log::level_from_string(
			sge::iconv(log_level)));

	sanguis::log().activate_hierarchy(
		sge::log::level_from_string(
			sge::iconv(log_level)));

	sge::systems::instance sys(
		sge::systems::list()
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sanguis::resolution(),
				sge::renderer::bit_depth::depth32),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed,
			sge::renderer::vsync::on))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::audio_player)
		(sge::systems::parameterless::image)
		(sge::systems::parameterless::font));

	// input stuff
	sge::input::key_state_tracker ks(sys.input_system());

	// font stuff
	sge::font::metrics_ptr const metrics = sys.font_system()->create_font(
		sge::media_path() / SGE_TEXT("fonts") / SGE_TEXT("default.ttf"),
		static_cast<sge::font::size_type>(15));
	sge::font::drawer_ptr const drawer(new sge::font::drawer_3d(sys.renderer()));
	sge::font::font font(metrics,drawer);
	sge::texture::manager texman(
		sys.renderer(),
		sge::texture::default_creator<sge::texture::no_fragmented>(
			sys.renderer(),
			sge::renderer::color_format::rgba8, // TODO: what do we want to use here?
			sge::renderer::linear_filter));
	sge::font::font_ptr const console_font(new sge::font::font(metrics,drawer));

	sge::con::console_gfx console(sys.renderer(),
		sge::texture::add(
			texman,
			sys.image_loader()->load(
				sanguis::media_path() / SGE_TEXT("console_back.jpg"))),
		console_font,
		sys.input_system(),
		sge::sprite::point(0,0),
		sge::sprite::dim(
			sys.renderer()->screen_size().w(),
			static_cast<sge::sprite::unit>(
				sys.renderer()->screen_size().h() / 2)));
	
	sge::audio::multi_loader audio_loader(sys.plugin_manager());
	sge::audio::pool_ptr sound_pool = sys.audio_player()->create_pool();

	sanguis::load::resource::connection resources(
		sys.image_loader(),
		sys.renderer(),
		audio_loader,
		sys.audio_player(),
		sound_pool);
	
	sanguis::server::machine server(
		console, 
		host_port);
	server.initiate();
	
	// construct and initialize statemachine
	sanguis::client::machine client(
		sys,
		sound_pool,
		font,
		ks,
		console,
		dest_server,
		dest_port);
	// this should construct, among others, the renderer
	client.initiate();

	sge::time::timer frame_timer(
		sge::time::second(1));

	bool running = true;
	while (running)
	{
		sanguis::tick_event t(static_cast<sanguis::time_type>(frame_timer.reset()));

		// get and send messages
		server.process(t);
		running = client.process(t);
	}
} catch (sge::exception const &e) {
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
} catch (std::exception const &e) {
	std::cerr << "caught standard exception: " << e.what() << '\n';
	return EXIT_FAILURE;
}
