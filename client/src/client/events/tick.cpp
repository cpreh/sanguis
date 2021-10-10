#include <sanguis/duration.hpp>
#include <sanguis/client/events/tick.hpp>

sanguis::client::events::tick::tick(sanguis::duration const &_delta) : delta_(_delta) {}

sanguis::client::events::tick::tick(tick &&) noexcept = default;

sanguis::client::events::tick::tick(tick const &) = default;

sanguis::client::events::tick &sanguis::client::events::tick::operator=(tick &&) noexcept = default;

sanguis::client::events::tick &sanguis::client::events::tick::operator=(tick const &) = default;

sanguis::client::events::tick::~tick() = default;

sanguis::duration const &sanguis::client::events::tick::delta() const { return delta_; }
