#ifndef SANGUIS_COLLISION_IMPL_RECT_LINE_INTERSECTION_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_RECT_LINE_INTERSECTION_HPP_INCLUDED

#include <sanguis/collision/impl/line_segment_fwd.hpp>
#include <sanguis/collision/impl/optional_intersection_fwd.hpp>
#include <sanguis/collision/impl/rect_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

sanguis::collision::impl::optional_intersection
rect_line_intersection(
	sanguis::collision::impl::rect,
	sanguis::collision::impl::line_segment
);

}
}
}

#endif
