#ifndef SANGUIS_COLLISION_AUX_ADJUST_SPEED_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_ADJUST_SPEED_HPP_INCLUDED

#include <sanguis/collision/dim2_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/aux/line_segment_fwd.hpp>
#include <sanguis/collision/aux/rect_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{

sanguis::collision::speed const
adjust_speed(
	sanguis::collision::aux::line_segment movement,
	sanguis::collision::dim2 entity_size,
	sanguis::collision::aux::rect obstacle,
	sanguis::collision::speed old_speed
);

}
}
}

#endif
