#ifndef SANGUIS_SERVER_NET_ANGLE_POLICY_HPP_INCLUDED
#define SANGUIS_SERVER_NET_ANGLE_POLICY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/angle_fwd.hpp>
#include <sanguis/server/net/angle_policy_fwd.hpp>

namespace sanguis::server::net
{

struct angle_policy
{
  static sanguis::duration start_duration();

  static sanguis::duration difference(sanguis::server::angle, sanguis::server::angle);
};

}

#endif
