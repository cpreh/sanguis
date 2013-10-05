#ifndef SANGUIS_SERVER_NET_HEALTH_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_NET_HEALTH_FWD_HPP_INCLUDED

#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/net/health_policy_fwd.hpp>
#include <sanguis/server/net/value_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

typedef
sanguis::server::net::value<
	sanguis::server::health,
	sanguis::server::net::health_policy
>
health;

}
}
}

#endif
