#ifndef SANGUIS_CREATOR_GRID_CRANGE_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_GRID_CRANGE_FWD_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <fcppt/container/grid/pos_ref_range_fwd.hpp>

namespace sanguis::creator
{

using grid_crange = fcppt::container::grid::pos_ref_range<sanguis::creator::grid const>;

}

#endif
