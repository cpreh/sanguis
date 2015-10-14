#include <sanguis/client/log.hpp>
#include <sanguis/client/server.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <functional>
#include <mutex>
#include <fcppt/config/external_end.hpp>


sanguis::client::server::server(
	alda::net::port const _port
)
:
	running_(
		true
	),
	impl_(
		_port
	),
	mutex_(),
	server_thread_(
		std::bind(
			&sanguis::client::server::mainloop,
			this
		)
	)
{
}

void
sanguis::client::server::quit()
{
	this->reset_running();

	impl_.stop();
}

bool
sanguis::client::server::running() const
{
	std::lock_guard<
		std::mutex
	> const lock(
		mutex_
	);

	return
		running_;
}

sanguis::client::server::~server()
{
}

awl::main::exit_code
sanguis::client::server::run()
{
	server_thread_.join();

	return
		awl::main::exit_success();
}

void
sanguis::client::server::mainloop()
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
			sanguis::client::log(),
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
			sanguis::client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Error in server thread: ")
				<< _exception.what()
		);
	}

	this->reset_running();
}

void
sanguis::client::server::reset_running()
{
	std::lock_guard<
		std::mutex
	> const lock(
		mutex_
	);

	running_ = false;
}
