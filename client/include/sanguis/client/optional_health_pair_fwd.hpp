#ifndef SANGUIS_CLIENT_OPTIONAL_HEALTH_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_OPTIONAL_HEALTH_PAIR_FWD_HPP_INCLUDED

#include <sanguis/client/health_pair_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::client
{

using
optional_health_pair
=
fcppt::optional::object<
	sanguis::client::health_pair
>;

}

#endif
