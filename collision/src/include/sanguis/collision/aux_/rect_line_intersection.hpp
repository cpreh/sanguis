#ifndef SANGUIS_COLLISION_AUX__RECT_LINE_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__RECT_LINE_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/aux_/line_segment_fwd.hpp>
#include <sanguis/collision/aux_/optional_intersection_fwd.hpp>
#include <sanguis/collision/aux_/rect_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{

sanguis::collision::aux_::optional_intersection const
rect_line_intersection(
	sanguis::collision::aux_::rect,
	sanguis::collision::aux_::line_segment
);

}
}
}

#endif
