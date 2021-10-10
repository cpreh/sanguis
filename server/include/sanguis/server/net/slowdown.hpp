#ifndef SANGUIS_SERVER_NET_SLOWDOWN_HPP_INCLUDED
#define SANGUIS_SERVER_NET_SLOWDOWN_HPP_INCLUDED

#include <sanguis/clock.hpp>
#include <sanguis/slowdown.hpp>
#include <sanguis/server/net/basic_value_decl.hpp>
#include <sanguis/server/net/slowdown_fwd.hpp>
#include <sanguis/server/net/slowdown_policy.hpp>

extern template class sanguis::server::net::
    basic_value<sanguis::slowdown, sanguis::server::net::slowdown_policy, sanguis::clock>;

#endif
