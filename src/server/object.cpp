#include <sanguis/main_object.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/object.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <functional>
#include <cstdlib>
#include <mutex>
#include <fcppt/config/external_end.hpp>


sanguis::server::object::object(
	alda::net::port const _port
)
:
	sanguis::main_object(),
	running_(
		true
	),
	impl_(
		_port
	),
	mutex_(),
	server_thread_(
		std::bind(
			&sanguis::server::object::mainloop,
			this
		)
	)
{
}

void
sanguis::server::object::quit()
{
	this->reset_running();

	impl_.stop();
}

bool
sanguis::server::object::running() const
{
	std::lock_guard<
		std::mutex
	> const lock(
		mutex_
	);

	return
		running_;
}

sanguis::server::object::~object()
{
}

awl::main::exit_code const
sanguis::server::object::run()
{
	server_thread_.join();

	return
		awl::main::exit_success();
}

void
sanguis::server::object::mainloop()
{
	try
	{
		impl_.run();
	}
	catch(
		fcppt::exception const &_exception
	)
	{
		FCPPT_LOG_ERROR(
			sanguis::server::log(),
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
			sanguis::server::log(),
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
	std::lock_guard<
		std::mutex
	> const lock(
		mutex_
	);

	running_ = false;
}
