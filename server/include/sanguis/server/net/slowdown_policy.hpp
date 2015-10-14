#ifndef SANGUIS_SERVER_NET_SLOWDOWN_POLICY_HPP_INCLUDED
#define SANGUIS_SERVER_NET_SLOWDOWN_POLICY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/slowdown_fwd.hpp>
#include <sanguis/server/net/slowdown_policy_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

struct slowdown_policy
{
	static
	sanguis::duration
	start_duration();

	static
	sanguis::duration
	difference(
		sanguis::slowdown,
		sanguis::slowdown
	);
};

}
}
}

#endif
