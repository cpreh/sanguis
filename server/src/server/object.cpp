#include <sanguis/server/object.hpp>
#include <sanguis/server/object_base.hpp>
#include <sanguis/server/events/disconnect.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/events/message.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/events/tick.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/states/running.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/states/unpaused.hpp> // NOLINT(misc-include-cleaner)
#include <alda/net/port.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/log/context_reference.hpp>

sanguis::server::object::object(
    fcppt::log::context_reference const _log_context, alda::net::port const _port)
    : sanguis::server::object_base(),
      io_service_(),
      machine_(_log_context, _port, fcppt::make_ref(io_service_)),
      scoped_machine_(fcppt::make_ref(machine_))
{
}

sanguis::server::object::~object() = default;

void sanguis::server::object::run() { io_service_.run(); }

void sanguis::server::object::stop() { io_service_.stop(); }
