#ifndef SANGUIS_SERVER_NET_SPEED_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_NET_SPEED_FWD_HPP_INCLUDED

#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/net/speed_policy_fwd.hpp>
#include <sanguis/server/net/value_fwd.hpp>

namespace sanguis::server::net
{

using speed =
    sanguis::server::net::value<sanguis::server::speed, sanguis::server::net::speed_policy>;

}

#endif
