#ifndef SANGUIS_SERVER_NET_ANGLE_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_NET_ANGLE_FWD_HPP_INCLUDED

#include <sanguis/server/angle_fwd.hpp>
#include <sanguis/server/net/angle_policy_fwd.hpp>
#include <sanguis/server/net/value_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

typedef
sanguis::server::net::value<
	sanguis::server::angle,
	sanguis::server::net::angle_policy
>
angle;

}
}
}

#endif
