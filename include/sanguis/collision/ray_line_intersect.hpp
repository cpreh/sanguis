#ifndef SANGUIS_COLLISION_RAY_LINE_INTERSECT_HPP_INCLUDED
#define SANGUIS_COLLISION_RAY_LINE_INTERSECT_HPP_INCLUDED

#include <sanguis/collision/line_segment_fwd.hpp>
#include <sanguis/collision/optional_vector2_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/vector2_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::optional_vector2 const
ray_line_intersect(
	sanguis::collision::vector2,
	sanguis::collision::speed,
	sanguis::collision::line_segment
);

}
}

#endif
