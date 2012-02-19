#include <sanguis/server/object.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/mainloop/asio/create_io_service_base.hpp>
#include <awl/mainloop/io_service.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>

sanguis::server::object::object(
	net::port const _port,
	load::context_base const &_load_context
)
:
	running_(
		true
	),
	io_service_(
		awl::mainloop::asio::create_io_service_base()
	),
	machine_(
		_load_context,
		_port,
		*io_service_
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

awl::main::exit_code const
sanguis::server::object::run()
{
	server_thread_.join();

	return awl::main::exit_success();
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
	}
	catch(
		std::exception const &_exception
	)
	{
		FCPPT_LOG_ERROR(
			server::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Error in server thread: ")
				<< _exception.what()
		);
	}

	this->reset_running();
}

void
sanguis::server::object::reset_running()
{
	boost::mutex::scoped_lock const lock(
		mutex_
	);

	running_ = false;
}
