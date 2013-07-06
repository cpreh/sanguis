#ifndef SANGUIS_COLLISION_RECT_LINE_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_RECT_LINE_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/line_segment_fwd.hpp>
#include <sanguis/collision/optional_intersection_fwd.hpp>
#include <sanguis/collision/rect_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::optional_intersection const
rect_line_intersection(
	sanguis::collision::rect,
	sanguis::collision::line_segment
);

}
}

#endif
