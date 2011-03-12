#include "object.hpp"
#include "log.hpp"
#include "message_event.hpp"
#include "states/running.hpp"
#include "states/unpaused.hpp"
#include "../time_type.hpp"
#include "../tick_event.hpp"
#include "../scoped_machine_impl.hpp"
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
	load::context_base const &load_context
)
:
	frame_timer_(
		sge::time::second(
			1
		)
	),
	machine_(
		load_context,
		sys.collision_system(),
		port_
	),
	timer_connection_(
		machine_.net().register_timer(
			std::tr1::bind(
				&object::timer_callback,
				this
			)
		)
	),
	running_(
		true
	),
	mutex_(),
	server_thread_(
		std::tr1::bind(
			&object::mainloop,
			this
		)
	),
	scoped_machine_(
		machine_
	)
{
}

void
sanguis::server::object::quit()
{
	reset_running();

	machine_.stop();
}

bool
sanguis::server::object::running()
{
	boost::mutex::scoped_lock const lock_(
		mutex_
	);

	return running_;
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
		while (running())
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

		reset_running();
	}
}

void
sanguis::server::object::timer_callback()
{
	machine_.process(
		tick_event(
			static_cast<
				time_type
			>(
				frame_timer_.reset()
			)
		)
	);
}

void
sanguis::server::object::reset_running()
{
	boost::mutex::scoped_lock const lock_(
		mutex_
	);
		
	running_ = false;
}
