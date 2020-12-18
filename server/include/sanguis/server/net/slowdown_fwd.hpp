#ifndef SANGUIS_SERVER_NET_SLOWDOWN_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_NET_SLOWDOWN_FWD_HPP_INCLUDED

#include <sanguis/clock.hpp>
#include <sanguis/slowdown_fwd.hpp>
#include <sanguis/server/net/basic_value_fwd.hpp>
#include <sanguis/server/net/slowdown_policy_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

using
slowdown
=
sanguis::server::net::basic_value<
	sanguis::slowdown,
	sanguis::server::net::slowdown_policy,
	sanguis::clock
>;

}
}
}

#endif
