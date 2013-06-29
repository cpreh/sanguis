#ifndef SANGUIS_COLLISION_BOTH_INTERSECTIONS_HPP_INCLUDED
#define SANGUIS_COLLISION_BOTH_INTERSECTIONS_HPP_INCLUDED

#include <sanguis/collision/intersection_pair_fwd.hpp>
#include <sanguis/collision/dir_fwd.hpp>
#include <sanguis/collision/pos_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::intersection_pair const
both_intersections(
	sanguis::creator::pos,
	sanguis::collision::dir,
	sanguis::collision::pos tangent1,
	sanguis::collision::pos tangent2
);

}
}

#endif
