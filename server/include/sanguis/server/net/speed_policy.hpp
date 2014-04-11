#ifndef SANGUIS_SERVER_NET_SPEED_POLICY_HPP_INCLUDED
#define SANGUIS_SERVER_NET_SPEED_POLICY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/net/speed_policy_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

struct speed_policy
{
	static
	sanguis::duration const
	start_duration();

	static
	sanguis::duration const
	difference(
		sanguis::server::speed,
		sanguis::server::speed
	);
};

}
}
}

#endif