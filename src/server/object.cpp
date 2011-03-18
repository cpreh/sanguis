#include "object.hpp"
#include "log.hpp"
#include "message_event.hpp"
#include "states/running.hpp"
#include "states/unpaused.hpp"
#include "../tick_event.hpp"
#include <sge/systems/instance.hpp>
#include <awl/mainloop/asio/create_io_service_base.hpp>
#include <awl/mainloop/io_service.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <cstdlib>

sanguis::server::object::object(
	sge::systems::instance const &_sys,
	net::port const _port,
	load::context_base const &_load_context
)
:
	io_service_(
		awl::mainloop::asio::create_io_service_base()
	),
	machine_(
		_load_context,
		_sys.collision_system(),
		_port,
		*io_service_
	),
	running_(
		true
	),
	scoped_machine_(
		machine_
	),
	mutex_(),
	server_thread_(
		std::tr1::bind(
			&object::mainloop,
			this
		)
	)
{
}

void
sanguis::server::object::quit()
{
	this->reset_running();

	machine_.stop();
}

bool
sanguis::server::object::running()
{
	boost::mutex::scoped_lock const lock(
		mutex_
	);

	return running_;
}

sanguis::server::object::~object()
{
}

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
		io_service_->run();
	}
	catch(
		fcppt::exception const &_exception
	)
	{
		FCPPT_LOG_ERROR(
			server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Error in server thread: ")
				<< _exception.string()
		);

		this->reset_running();
	}
}

void
sanguis::server::object::reset_running()
{
	boost::mutex::scoped_lock const lock(
		mutex_
	);
		
	running_ = false;
}
