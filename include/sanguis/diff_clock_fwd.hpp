#ifndef SANGUIS_DIFF_CLOCK_FWD_HPP_INCLUDED
#define SANGUIS_DIFF_CLOCK_FWD_HPP_INCLUDED

#include <sanguis/clock.hpp>
#include <sge/timer/clocks/delta_fwd.hpp>

namespace sanguis
{

typedef sge::timer::clocks::delta<
	sanguis::clock
> diff_clock;

}

#endif
