#ifndef SANGUIS_CLIENT_MAX_HEALTH_HPP_INCLUDED
#define SANGUIS_CLIENT_MAX_HEALTH_HPP_INCLUDED

#include <sanguis/client/health_value.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis::client
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::client::health_value,
	max_health
);

}

#endif
