#include <sanguis/server/weapons/events/stop.hpp>

sanguis::server::weapons::events::stop::stop() = default;

sanguis::server::weapons::events::stop::stop(stop &&) noexcept = default;

sanguis::server::weapons::events::stop::stop(stop const &) = default;

sanguis::server::weapons::events::stop &
sanguis::server::weapons::events::stop::operator=(stop &&) noexcept = default;

sanguis::server::weapons::events::stop &
sanguis::server::weapons::events::stop::operator=(stop const &) = default;

sanguis::server::weapons::events::stop::~stop() = default;
