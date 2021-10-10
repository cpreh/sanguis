#include <sanguis/server/health.hpp>
#include <sanguis/server/net/health.hpp>
#include <sanguis/server/net/health_policy.hpp>
#include <sanguis/server/net/instantiate_value.hpp>

SANGUIS_SERVER_NET_INSTANTIATE_VALUE(sanguis::server::health, sanguis::server::net::health_policy);
