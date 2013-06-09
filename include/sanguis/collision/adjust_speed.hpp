#ifndef SANGUIS_COLLISION_ADJUST_SPEED_HPP_INCLUDED
#define SANGUIS_COLLISION_ADJUST_SPEED_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::speed const
adjust_speed(
	sanguis::creator::pos,
	sanguis::collision::speed,
	sanguis::collision::center,
	sanguis::collision::radius
);

}
}

#endif
