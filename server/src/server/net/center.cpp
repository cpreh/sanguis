#include <sanguis/server/center.hpp>
#include <sanguis/server/net/center.hpp>
#include <sanguis/server/net/center_policy.hpp>
#include <sanguis/server/net/instantiate_value.hpp>


SANGUIS_SERVER_NET_INSTANTIATE_VALUE(
	sanguis::server::center,
	sanguis::server::net::center_policy
);
