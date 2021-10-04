#ifndef SANGUIS_SERVER_COLLISION_FROM_SPEED_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_FROM_SPEED_HPP_INCLUDED

#include <sanguis/collision/speed.hpp>
#include <sanguis/server/speed_fwd.hpp>


namespace sanguis::server::collision
{

sanguis::server::speed
from_speed(
	sanguis::collision::speed const &
);

}

#endif
