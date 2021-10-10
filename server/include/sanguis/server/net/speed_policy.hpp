#ifndef SANGUIS_SERVER_NET_SPEED_POLICY_HPP_INCLUDED
#define SANGUIS_SERVER_NET_SPEED_POLICY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/net/speed_policy_fwd.hpp>

namespace sanguis::server::net
{

struct speed_policy
{
  static sanguis::duration start_duration();

  static sanguis::duration
  difference(sanguis::server::speed const &, sanguis::server::speed const &);
};

}

#endif
