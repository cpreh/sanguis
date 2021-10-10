#ifndef SANGUIS_DIFF_CLOCK_CREF_HPP_INCLUDED
#define SANGUIS_DIFF_CLOCK_CREF_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <fcppt/reference_impl.hpp>

namespace sanguis
{

using diff_clock_cref = fcppt::reference<sanguis::diff_clock const>;

}

#endif
