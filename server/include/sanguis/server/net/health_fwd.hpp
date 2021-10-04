#ifndef SANGUIS_SERVER_NET_HEALTH_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_NET_HEALTH_FWD_HPP_INCLUDED

#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/net/health_policy_fwd.hpp>
#include <sanguis/server/net/value_fwd.hpp>


namespace sanguis::server::net
{

using
health
=
sanguis::server::net::value<
	sanguis::server::health,
	sanguis::server::net::health_policy
>;

}

#endif
