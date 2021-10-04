#ifndef SANGUIS_COLLISION_IMPL_MAKE_RANGE_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_MAKE_RANGE_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/creator/grid_crange_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>


namespace sanguis::collision::impl
{

sanguis::creator::grid_crange
make_range(
	sanguis::creator::grid const &,
	sanguis::collision::center const &,
	sanguis::collision::radius const &
);

}

#endif
