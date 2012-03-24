#ifndef SANGUIS_UPDATE_DIFF_CLOCK_HPP_INCLUDED
#define SANGUIS_UPDATE_DIFF_CLOCK_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration.hpp>


namespace sanguis
{

void
update_diff_clock(
	sanguis::diff_clock &,
	sanguis::duration const &
);

}

#endif
