#ifndef SANGUIS_COLLISION_IMPL_LINE_LINE_INTERSECT_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_LINE_LINE_INTERSECT_HPP_INCLUDED

#include <sanguis/collision/impl/line_segment_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

bool
line_line_intersect(
	sanguis::collision::impl::line_segment const &,
	sanguis::collision::impl::line_segment const &
);

}
}
}

#endif
