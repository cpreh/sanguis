#include <sanguis/duration.hpp>
#include <sanguis/slowdown.hpp>
#include <sanguis/server/events/tick.hpp>

sanguis::server::events::tick::tick(
    sanguis::duration const &_delta, sanguis::slowdown const _slowdown)
    : delta_{_delta}, slowdown_{_slowdown}
{
}

sanguis::server::events::tick::tick(tick &&) noexcept = default;

sanguis::server::events::tick::tick(tick const &) = default;

sanguis::server::events::tick &sanguis::server::events::tick::operator=(tick &&) noexcept = default;

sanguis::server::events::tick &sanguis::server::events::tick::operator=(tick const &) = default;

sanguis::server::events::tick::~tick() = default;

sanguis::duration const &sanguis::server::events::tick::delta() const { return delta_; }

sanguis::slowdown sanguis::server::events::tick::slowdown() const { return slowdown_; }
