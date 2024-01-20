#ifndef SANGUIS_SERVER_NET_CENTER_POLICY_HPP_INCLUDED
#define SANGUIS_SERVER_NET_CENTER_POLICY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/net/center_policy_fwd.hpp> // IWYU pragma: keep

namespace sanguis::server::net
{

struct center_policy
{
  static sanguis::duration start_duration();

  static sanguis::duration
  difference(sanguis::server::center const &, sanguis::server::center const &);
};

}

#endif
