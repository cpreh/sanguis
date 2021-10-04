#ifndef SANGUIS_CLIENT_SLOWED_DURATION_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_SLOWED_DURATION_FWD_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis::client
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sanguis::duration,
	slowed_duration
);

}

#endif
