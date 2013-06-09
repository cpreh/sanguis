#ifndef SANGUIS_COLLISION_ADJUST_SPEED_ONE_HPP_INCLUDED
#define SANGUIS_COLLISION_ADJUST_SPEED_ONE_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/rect_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/vector2_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::speed const
adjust_speed_one(
	sanguis::collision::center,
	sanguis::collision::speed,
	sanguis::collision::radius,
	sanguis::collision::rect,
	sanguis::collision::vector2
);

}
}

#endif
