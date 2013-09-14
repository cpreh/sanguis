#ifndef SANGUIS_COLLISION_AUX__ADJUST_SPEED_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__ADJUST_SPEED_HPP_INCLUDED

#include <sanguis/collision/dim2_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/aux_/line_segment_fwd.hpp>
#include <sanguis/collision/aux_/rect_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{

sanguis::collision::speed const
adjust_speed(
	sanguis::collision::aux_::line_segment movement,
	sanguis::collision::dim2 entity_size,
	sanguis::collision::aux_::rect obstacle,
	sanguis::collision::speed old_speed
);

}
}
}

#endif
