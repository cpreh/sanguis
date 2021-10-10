#include <sanguis/server/weapons/events/poll.hpp>

sanguis::server::weapons::events::poll::poll() = default;

sanguis::server::weapons::events::poll::poll(poll &&) noexcept = default;

sanguis::server::weapons::events::poll::poll(poll const &) = default;

sanguis::server::weapons::events::poll &
sanguis::server::weapons::events::poll::operator=(poll &&) noexcept = default;

sanguis::server::weapons::events::poll &
sanguis::server::weapons::events::poll::operator=(poll const &) = default;

sanguis::server::weapons::events::poll::~poll() = default;
