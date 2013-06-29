#ifndef SANGUIS_COLLISION_ADJUST_SPEED_HPP_INCLUDED
#define SANGUIS_COLLISION_ADJUST_SPEED_HPP_INCLUDED

#include <sanguis/collision/intersection_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::speed const
adjust_speed(
	sanguis::collision::intersection,
	sanguis::collision::speed
);

}
}

#endif
