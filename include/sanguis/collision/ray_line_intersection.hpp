#ifndef SANGUIS_COLLISION_RAY_LINE_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_RAY_LINE_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/dir_fwd.hpp>
#include <sanguis/collision/line_segment_fwd.hpp>
#include <sanguis/collision/optional_unit_fwd.hpp>
#include <sanguis/collision/pos_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::optional_unit const
ray_line_intersection(
	sanguis::collision::pos,
	sanguis::collision::dir,
	sanguis::collision::line_segment
);

}
}

#endif
