#ifndef SANGUIS_UPDATE_DIFF_CLOCK_HPP_INCLUDED
#define SANGUIS_UPDATE_DIFF_CLOCK_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/common/symbol.hpp>

namespace sanguis
{

SANGUIS_COMMON_SYMBOL
void update_diff_clock(
    sanguis::diff_clock &, // NOLINT(google-runtime-references)
    sanguis::duration const &);

}

#endif
