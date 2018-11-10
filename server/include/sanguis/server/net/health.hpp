#ifndef SANGUIS_SERVER_NET_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_NET_HEALTH_HPP_INCLUDED

#include <sanguis/server/health.hpp>
#include <sanguis/server/net/health_fwd.hpp>
#include <sanguis/server/net/health_policy.hpp>
#include <sanguis/server/net/declare_value.hpp>


SANGUIS_SERVER_NET_DECLARE_VALUE(
	sanguis::server::health,
	sanguis::server::net::health_policy
);

#endif
