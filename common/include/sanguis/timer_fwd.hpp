#ifndef SANGUIS_TIMER_FWD_HPP_INCLUDED
#define SANGUIS_TIMER_FWD_HPP_INCLUDED

#include <sanguis/clock.hpp>
#include <sge/timer/basic_fwd.hpp>


namespace sanguis
{

typedef
sge::timer::basic<
	sanguis::clock
>
timer;

}

#endif
