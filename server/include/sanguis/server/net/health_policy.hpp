#ifndef SANGUIS_SERVER_NET_HEALTH_POLICY_HPP_INCLUDED
#define SANGUIS_SERVER_NET_HEALTH_POLICY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/net/health_policy_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

struct health_policy
{
	static
	sanguis::duration
	start_duration();

	static
	sanguis::duration
	difference(
		sanguis::server::health,
		sanguis::server::health
	);
};

}
}
}

#endif
