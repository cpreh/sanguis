#ifndef SANGUIS_SERVER_NET_CENTER_POLICY_HPP_INCLUDED
#define SANGUIS_SERVER_NET_CENTER_POLICY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/net/center_policy_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace net
{

struct center_policy
{
	static
	sanguis::duration const
	start_duration();

	static
	sanguis::duration const
	difference(
		sanguis::server::center,
		sanguis::server::center
	);
};

}
}
}

#endif
