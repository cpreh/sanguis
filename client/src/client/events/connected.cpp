#include <sanguis/client/events/connected.hpp>

sanguis::client::events::connected::connected() = default;

sanguis::client::events::connected::connected(connected &&) noexcept = default;

sanguis::client::events::connected::connected(connected const &) = default;

sanguis::client::events::connected &
sanguis::client::events::connected::operator=(connected &&) noexcept = default;

sanguis::client::events::connected &
sanguis::client::events::connected::operator=(connected const &) = default;

sanguis::client::events::connected::~connected() = default;
