#ifndef SANGUIS_TIME_DELTA_FWD_HPP_INCLUDED
#define SANGUIS_TIME_DELTA_FWD_HPP_INCLUDED

#include "time_unit.hpp"
#include <fcppt/chrono/duration_fwd.hpp>

namespace sanguis
{

typedef fcppt::chrono::duration<
	sanguis::time_unit
> time_delta;

}

#endif
