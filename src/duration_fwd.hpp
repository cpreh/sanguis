#ifndef SANGUIS_DURATION_FWD_HPP_INCLUDED
#define SANGUIS_DURATION_FWD_HPP_INCLUDED

#include "time_unit.hpp"
#include <fcppt/chrono/duration_fwd.hpp>

namespace sanguis
{

typedef fcppt::chrono::duration<
	sanguis::time_unit
> duration;

}

#endif
