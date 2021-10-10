#ifndef SANGUIS_DIFF_CLOCK_FWD_HPP_INCLUDED
#define SANGUIS_DIFF_CLOCK_FWD_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sge/timer/clocks/delta_fwd.hpp>

namespace sanguis
{

using diff_clock = sge::timer::clocks::delta<sanguis::duration>;

}

#endif
