#include <sanguis/server/speed.hpp>
#include <sanguis/server/net/instantiate_value.hpp>
#include <sanguis/server/net/speed.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/net/speed_policy.hpp>

SANGUIS_SERVER_NET_INSTANTIATE_VALUE(sanguis::server::speed, sanguis::server::net::speed_policy);
