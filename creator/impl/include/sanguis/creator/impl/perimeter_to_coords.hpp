#ifndef SANGUIS_CREATOR_IMPL_PERIMETER_TO_COORDS_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_PERIMETER_TO_COORDS_HPP_INCLUDED

#include <sanguis/creator/grid.hpp>

namespace sanguis::creator::impl
{

/**
 * Coordinates of a point on the perimeter of a rectangle ((0,0),(w,h)),
 * excluding the corners.
 * The order of traversal is as follows. Example: (w = 4, h = 3)
 * x 0 1 x
 * 5     2
 * x 4 3 x
 */
sanguis::creator::grid::pos
perimeter_to_coords(sanguis::creator::grid::dim const &, unsigned const &);

}

#endif
