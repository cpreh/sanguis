#include <sanguis/clock.hpp>
#include <sanguis/slowdown.hpp>
#include <sanguis/server/net/basic_value_impl.hpp>
#include <sanguis/server/net/slowdown.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/net/slowdown_policy.hpp>

template class sanguis::server::net::
    basic_value<sanguis::slowdown, sanguis::server::net::slowdown_policy, sanguis::clock>;
