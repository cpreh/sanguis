#include <sanguis/server/common_object.hpp>
#include <sanguis/server/events/disconnect.hpp>
#include <sanguis/server/events/message.hpp>
#include <sanguis/server/events/tick.hpp>
#include <sanguis/server/states/running.hpp>
#include <sanguis/server/states/unpaused.hpp>
#include <alda/net/port.hpp>


sanguis::server::common_object::common_object(
	alda::net::port const _port
)
:
	io_service_(),
	machine_(
		_port,
		io_service_
	),
	scoped_machine_(
		machine_
	)
{
}

sanguis::server::common_object::~common_object()
{
}

void
sanguis::server::common_object::run()
{
	io_service_.run();
}

void
sanguis::server::common_object::stop()
{
	io_service_.stop();
}
