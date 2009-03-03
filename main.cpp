// own
#include "server/machine.hpp"
#include "server/states/start.hpp"
#include "client/machine.hpp"
#include "client/states/start.hpp"
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
#include <sge/media.hpp>
#include <sge/make_shared_ptr.hpp>
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
#include <sge/audio/player.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/renderer/colors.hpp>
#include <sge/input/key_state_tracker.hpp>

// boost
#include <boost/filesystem.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/program_options.hpp>

// c++
#include <exception>
#include <iostream>
#include <fstream>
#include <ostream>
#include <memory>

// c
#include <cstdlib>

namespace
{

typedef std::auto_ptr<
	sanguis::server::machine
> server_auto_ptr;

server_auto_ptr
create_server(
	sanguis::load::context const &,
	sge::collision::system_ptr const,
	sge::console::gfx &,
	::net::port_type,
	bool client_only);

}

int main(int argc,char *argv[])
try
{
	namespace po = boost::program_options;
	po::options_description desc("allowed options");

	net::address_type dest_server;
	net::port_type host_port,dest_port;
	std::string log_level;
	bool client_only;
	unsigned screen_width, screen_height;

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
		("client-only",
			po::value<bool>(&client_only)->default_value(false),
			"tells if we want to create a server or not")
		("log",
			po::value<std::string>(&log_level)->default_value(std::string("warning")),
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
		sge::renderer::screen_size_t(
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
		(sge::systems::parameterless::collision_system)
		(sge::systems::parameterless::font));

	// input stuff
	sge::input::key_state_tracker ks(sys.input_system());

	// font stuff
	sge::font::metrics_ptr const metrics = sys.font_system()->create_font(
		sge::media_path() / SGE_TEXT("fonts") / SGE_TEXT("default.ttf"),
		static_cast<sge::font::size_type>(15));
	sge::font::drawer_ptr const drawer(
		sge::make_shared_ptr<sge::font::drawer_3d>(
			sys.renderer(),
			sge::renderer::colors::white()));
	sge::font::object font(metrics,drawer);
	sge::texture::manager texman(
		sys.renderer(),
		sge::texture::default_creator<sge::texture::no_fragmented>(
			sys.renderer(),
			sge::renderer::color_format::rgba8, // TODO: what do we want to use here?
			sge::renderer::filter::linear));

	sge::console::object console(SGE_TEXT('/'));

	sge::console::gfx console_gfx(
		console,
		sys.renderer(),
		sge::renderer::rgba8_color(255,255,255,255),
		metrics,
		sys.input_system(),
		sge::sprite::object(
			sge::sprite::point(0,0),
			sge::texture::const_part_ptr(
				sge::texture::add_image(
					texman,
					sys.image_loader()->load(
						sanguis::media_path() / SGE_TEXT("console_back.jpg")))),
			sge::sprite::dim(
				sys.renderer()->screen_size().w(),
				static_cast<sge::sprite::unit>(
					sys.renderer()->screen_size().h() / 2))
			)
		);
	
	sge::audio::multi_loader audio_loader(sys.plugin_manager());
	sge::audio::pool sound_pool;

	sanguis::load::context resources(
		sys.image_loader(),
		sys.renderer(),
		audio_loader,
		sys.audio_player(),
		sound_pool);
	
	resources.preload();

	boost::scoped_ptr<
		sanguis::server::machine
	> server(
		create_server(
			resources,
			sys.collision_system(),
			console_gfx,
			host_port,
			client_only));

	if(server)
		server->initiate();
	/*
	sanguis::server::machine server(
		console, 
		host_port);
	server.initiate();*/
	
	// construct and initialize statemachine
	sanguis::client::machine client(
		resources,
		sys,
		sound_pool,
		font,
		ks,
		console_gfx,
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
		if(server)
			server->process(t);
		//server.process(t);
		running = client.process(t);
	}
} catch (sge::exception const &e) {
	sge::cerr << SGE_TEXT("caught sge exception: ") << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
} catch (std::exception const &e) {
	std::cerr << "caught standard exception: " << e.what() << '\n';
	return EXIT_FAILURE;
}

namespace
{

server_auto_ptr
create_server(
	sanguis::load::context const &resources,
	sge::collision::system_ptr const coll,
	sge::console::gfx &con,
	::net::port_type const host_port,
	bool const client_only)
{
	return !client_only
		? server_auto_ptr(
			new sanguis::server::machine(
				resources,
				coll,
				con, 
				host_port))
		: server_auto_ptr();

}

}
