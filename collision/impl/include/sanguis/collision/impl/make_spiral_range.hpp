#ifndef SANGUIS_COLLISION_IMPL_MAKE_SPIRAL_RANGE_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_MAKE_SPIRAL_RANGE_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/creator/grid_spiral_range.hpp>

namespace sanguis::collision::impl
{

sanguis::creator::grid_spiral_range
make_spiral_range(sanguis::collision::center const &, sanguis::collision::radius const &);

}

#endif
