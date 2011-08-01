#ifndef SANGUIS_DIFF_TIMER_HPP_INCLUDED
#define SANGUIS_DIFF_TIMER_HPP_INCLUDED

#include "diff_clock.hpp"
#include <sge/timer/basic.hpp>

namespace sanguis
{

typedef sge::timer::basic<
	sanguis::diff_clock
> diff_timer;

}

#endif
