#ifndef SANGUIS_CREATOR_GRID_SPIRAL_RANGE_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_GRID_SPIRAL_RANGE_FWD_HPP_INCLUDED

#include <sanguis/creator/signed_pos_fwd.hpp>
#include <fcppt/container/grid/spiral_range_fwd.hpp>


namespace sanguis::creator
{

using
grid_spiral_range
=
fcppt::container::grid::spiral_range<
	sanguis::creator::signed_pos
>;

}

#endif
