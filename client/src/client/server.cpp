#include <sanguis/log_parameters.hpp>
#include <sanguis/client/log_location.hpp>
#include <sanguis/client/server.hpp>
#include <alda/net/port.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <functional>
#include <mutex>
#include <fcppt/config/external_end.hpp>


sanguis::client::server::server(
	fcppt::log::context &_log_context,
	alda::net::port const _port
)
:
	log_{
		_log_context,
		sanguis::client::log_location(),
		sanguis::log_parameters(
			fcppt::log::name{
				FCPPT_TEXT("server")
			}
		)
	},
	running_(
		true
	),
	impl_(
		// TODO: Add server log options here
		_log_context,
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
			log_,
			fcppt::log::out
				<< FCPPT_TEXT("Error in server thread: ")
				<< _exception.string()
		)
	}
	catch(
		std::exception const &_exception
	)
	{
		FCPPT_LOG_ERROR(
			log_,
			fcppt::log::out
				<< FCPPT_TEXT("Error in server thread: ")
				<< _exception.what()
		)
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
