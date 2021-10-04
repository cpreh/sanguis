#ifndef SANGUIS_COLLISION_SPEED_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_SPEED_FWD_HPP_INCLUDED

#include <sanguis/collision/velocity_fwd.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sanguis::collision
{

using
speed
=
fcppt::math::vector::static_<
	sanguis::collision::velocity,
	2
>;

}

#endif
