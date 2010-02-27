#include "object.hpp"
#include "../args/server_port.hpp"
#include "../time_type.hpp"
#include "../tick_event.hpp"
#include <sge/systems/instance.hpp>
#include <sge/time/second.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/io/cerr.hpp>
#include <cstdlib>

sanguis::server::object::object(
	sge::systems::instance const &sys,
	boost::program_options::variables_map const &vm,
	load::context_base const &load_context)
:
	frame_timer_(
		sge::time::second(
			static_cast<sge::time::unit>(
				1))),
	machine_(
		load_context,
		sys.collision_system(),
		args::server_port(
			vm)),
	timer_connection_(
		machine_.net().register_timer(
			std::tr1::bind(
				&object::timer_callback,
				this))),
	server_thread_(
		std::tr1::bind(
			&object::mainloop,
			this)),
	running_(
		true)
{
}

void
sanguis::server::object::quit()
{
	running_ = false;
	machine_.stop();
}

sanguis::server::object::~object()
{}

int
sanguis::server::object::run()
{
	server_thread_.join();
	return EXIT_SUCCESS;
}

void
sanguis::server::object::mainloop()
{
	while (running_)
	{
		fcppt::io::cerr << "mainloop()\n";
		machine_.run();
	}
}

void
sanguis::server::object::timer_callback()
{
	fcppt::io::cerr << "timer_callback()\n";
	sge::time::timer::frames_type const f = 
		frame_timer_.elapsed_frames();
	frame_timer_.reset();
	machine_.process(
		tick_event(
			static_cast<time_type>(
				f)));
}
