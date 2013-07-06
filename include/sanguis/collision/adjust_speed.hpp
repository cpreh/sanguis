#ifndef SANGUIS_COLLISION_ADJUST_SPEED_HPP_INCLUDED
#define SANGUIS_COLLISION_ADJUST_SPEED_HPP_INCLUDED

#include <sanguis/collision/dim2_fwd.hpp>
#include <sanguis/collision/line_segment_fwd.hpp>
#include <sanguis/collision/rect_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::speed const
adjust_speed(
	sanguis::collision::line_segment movement,
	sanguis::collision::dim2 entity_size,
	sanguis::collision::rect obstacle,
	sanguis::collision::speed old_speed
);

}
}

#endif
