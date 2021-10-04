#ifndef SANGUIS_SERVER_NET_VALUE_FWD_HPP_INCLUDED
#define SANGUIS_SERVER_NET_VALUE_FWD_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/net/basic_value_fwd.hpp>


namespace sanguis::server::net
{

template<
	typename Type,
	typename Policy
>
using
value
=
sanguis::server::net::basic_value<
	Type,
	Policy,
	sanguis::diff_clock
>;

}

#endif
