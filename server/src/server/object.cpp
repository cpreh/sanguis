#include <sanguis/server/object.hpp>
#include <sanguis/server/object_base.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <alda/net/port.hpp>
#include <fcppt/log/context_fwd.hpp>


sanguis::server::object::object(
	fcppt::log::context &_log_context,
	alda::net::port const _port
)
:
	sanguis::server::object_base(),
	io_service_(),
	machine_(
		_log_context,
		_port,
		io_service_
	),
	scoped_machine_(
		machine_
	)
{
}

sanguis::server::object::~object()
{
}

void
sanguis::server::object::run()
{
	io_service_.run();
}

void
sanguis::server::object::stop()
{
	io_service_.stop();
}
