#include "object.hpp"
#include "log.hpp"
#include "message_event.hpp"
#include "states/running.hpp"
#include "states/unpaused.hpp"
#include "../time_type.hpp"
#include "../tick_event.hpp"
#include <sge/systems/instance.hpp>
#include <sge/time/second.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <cstdlib>

sanguis::server::object::object(
	sge::systems::instance const &sys,
	net::port_type const port_,
	load::context_base const &load_context)
:
	frame_timer_(
		sge::time::second(
			static_cast<sge::time::unit>(
				1))),
	machine_(
		load_context,
		sys.collision_system(),
		port_
	),
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
	machine_.initiate();
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
	try
	{
		while (running_)
			machine_.run();
	}
	catch(
		fcppt::exception const &e
	)
	{
		FCPPT_LOG_ERROR(
			log(),
			fcppt::log::_
				<< FCPPT_TEXT("Error in server thread: ")
				<< e.string()
		);
	}
}

void
sanguis::server::object::timer_callback()
{
	sge::time::timer::frames_type const f = 
		frame_timer_.elapsed_frames();
	frame_timer_.reset();
	machine_.process(
		tick_event(
			static_cast<time_type>(
				f)));
}
