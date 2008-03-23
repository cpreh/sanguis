// own
#include "server/machine.hpp"
#include "server/start_state.hpp"
#include "client/machine.hpp"
#include "client/start_state.hpp"
#include "tick_event.hpp"
#include "open_bytes.hpp"

// sge
#include <sge/iostream.hpp>
#include <sge/string.hpp>
#include <sge/exception.hpp>
#include <sge/console/console.hpp>
#include <sge/systems.hpp>
#include <sge/init.hpp>
#include <sge/media.hpp>
#include <sge/font/font_drawer_3d.hpp>
#include <sge/font/font.hpp>

// boost
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

// c++
#include <exception>
#include <iostream>
#include <iomanip>
#include <fstream>

// c
#include <cstdlib>

int main(int argc,char *argv[])
try
{
	namespace po = boost::program_options;
	po::options_description desc("allowed options");

	net::address_type dest_server;
	net::port_type host_port,dest_port;

	desc.add_options()
	    ("help","produce help message")
			("dest-server",po::value<net::address_type>(&dest_server)->default_value("localhost"),"sets the server (ip/hostname) to connect to when hitting space")
			("dest-port",po::value<net::port_type>(&dest_port)->default_value(1337),"sets the server port to connect to")
			("host-port",po::value<net::port_type>(&host_port)->default_value(1337),"sets the port to listen to for games");

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
		std::cout << desc << "\n";
		return EXIT_SUCCESS;
	}

	sge::systems sys;

	// basic stuff
	sys.init<sge::init::core>();
	sys.init<sge::init::renderer>(640, 480);
	sys.init<sge::init::input>();
	sys.init<sge::init::image_loader>();

	// input stuff
	sge::key_state_tracker ks(sys.input_system);

	// font stuff
	sge::plugin<sge::font_system>::ptr_type font_plugin = sys.plugin_manager.get_plugin<sge::font_system>().load();
	sge::font_system_ptr fs(font_plugin->get()());
	sge::font_metrics_ptr metrics = fs->create_font(sge::media_path() / SGE_TEXT("fonts/default.ttf"),15);
	sge::font_drawer_ptr drawer(new sge::font_drawer_3d(sys.renderer));
	sge::font font(metrics,drawer);
	
	sanguis::server::machine server(host_port);
	server.initiate();
	
	// construct and initialize statemachine
	sanguis::client::machine client(sys,font,ks,dest_server,dest_port);
	// this should construct, among others, the renderer
	client.initiate();

	sge::timer frame_timer(sge::second());

	bool running = true;
	while (running)
	{
		sge::cout << "open_bytes: " << std::setw(6) << open_bytes << "\r";
		
		sanguis::tick_event t(sanguis::tick_data(frame_timer.reset()));

		// get and send messages
		server.process(t);
		running = client.process(t);
	}
	sge::clog << SGE_TEXT("exiting...\n");
} catch (const sge::exception &e) {
	std::cerr << "caught sge exception: " << e.what() << "\n";
	return EXIT_FAILURE;
} catch (const std::exception &e) {
	std::cerr << "caught standard exception: " << e.what() << "\n";
	return EXIT_FAILURE;
}
