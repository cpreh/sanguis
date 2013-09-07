#ifndef SANGUIS_COLLISION_AUX_RECT_LINE_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_RECT_LINE_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/aux/line_segment_fwd.hpp>
#include <sanguis/collision/aux/optional_intersection_fwd.hpp>
#include <sanguis/collision/aux/rect_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{

sanguis::collision::aux::optional_intersection const
rect_line_intersection(
	sanguis::collision::aux::rect,
	sanguis::collision::aux::line_segment
);

}
}
}

#endif
