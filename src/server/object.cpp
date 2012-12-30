#include <sanguis/load/context_base_fwd.hpp>
#include <sanguis/server/object.hpp>
#include <sanguis/server/log.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <sge/charconv/system_fwd.hpp>
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
#include <fcppt/config/external_end.hpp>


sanguis::server::object::object(
	alda::net::port const _port,
	sanguis::load::context_base const &_load_context,
	sge::charconv::system &_charconv_system
)
:
	running_(
		true
	),
	io_service_(),
	machine_(
		_load_context,
		_charconv_system,
		_port,
		io_service_
	),
	scoped_machine_(
		machine_
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
		io_service_.run();
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
	boost::mutex::scoped_lock const lock(
		mutex_
	);

	running_ = false;
}
