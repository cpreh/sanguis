#ifndef SANGUIS_SERVER_NET_INSTANTIATE_VALUE_HPP_INCLUDED
#define SANGUIS_SERVER_NET_INSTANTIATE_VALUE_HPP_INCLUDED

#include <sanguis/diff_clock.hpp> // IWYU pragma: keep
#include <sanguis/server/net/basic_value_impl.hpp> // IWYU pragma: keep

#define SANGUIS_SERVER_NET_INSTANTIATE_VALUE(type, policy) \
  template class sanguis::server::net::basic_value<type, policy, sanguis::diff_clock>

#endif
