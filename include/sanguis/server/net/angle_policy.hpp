#ifndef SANGUIS_SERVER_NET_ANGLE_POLICY_HPP_INCLUDED
#define SANGUIS_SERVER_NET_ANGLE_POLICY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/angle_fwd.hpp>
#include <sanguis/server/net/angle_policy_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

struct angle_policy
{
	static
	sanguis::duration const
	start_duration();

	static
	sanguis::duration const
	difference(
		sanguis::server::angle,
		sanguis::server::angle
	);
};

}
}
}

#endif
