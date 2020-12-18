#ifndef SANGUIS_SERVER_NET_CENTER_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_NET_CENTER_FWD_HPP_INCLUDED

#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/net/center_policy_fwd.hpp>
#include <sanguis/server/net/value_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

using
center
=
sanguis::server::net::value<
	sanguis::server::center,
	sanguis::server::net::center_policy
>;

}
}
}

#endif
