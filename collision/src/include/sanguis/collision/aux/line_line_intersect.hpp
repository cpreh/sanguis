#ifndef SANGUIS_COLLISION_AUX_LINE_LINE_INTERSECT_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_LINE_LINE_INTERSECT_HPP_INCLUDED

#include <sanguis/collision/aux/line_segment_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{

bool
line_line_intersect(
	sanguis::collision::aux::line_segment,
	sanguis::collision::aux::line_segment
);

}
}
}

#endif
