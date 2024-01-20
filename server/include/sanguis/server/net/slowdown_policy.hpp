#ifndef SANGUIS_SERVER_NET_SLOWDOWN_POLICY_HPP_INCLUDED
#define SANGUIS_SERVER_NET_SLOWDOWN_POLICY_HPP_INCLUDED

#include <sanguis/clock.hpp>
#include <sanguis/slowdown_fwd.hpp>
#include <sanguis/server/net/slowdown_policy_fwd.hpp> // IWYU pragma: keep

namespace sanguis::server::net
{

struct slowdown_policy
{
  static sanguis::clock::duration start_duration();

  static sanguis::clock::duration difference(sanguis::slowdown, sanguis::slowdown);
};

}

#endif
