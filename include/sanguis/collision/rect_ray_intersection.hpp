#ifndef SANGUIS_COLLISION_RECT_RAY_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_RECT_RAY_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/dir_fwd.hpp>
#include <sanguis/collision/optional_intersection_fwd.hpp>
#include <sanguis/collision/pos_fwd.hpp>
#include <sanguis/collision/rect_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::optional_intersection const
rect_ray_intersection(
	sanguis::collision::rect,
	sanguis::collision::pos,
	sanguis::collision::dir
);

}
}

#endif
