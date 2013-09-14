#ifndef SANGUIS_COLLISION_AUX__MAKE_RANGE_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__MAKE_RANGE_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/dim2_fwd.hpp>
#include <sanguis/creator/grid_crange_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{

sanguis::creator::grid_crange const
make_range(
	sanguis::creator::grid const &,
	sanguis::collision::center,
	sanguis::collision::dim2
);

}
}
}

#endif
