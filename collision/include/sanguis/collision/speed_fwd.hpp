#ifndef SANGUIS_COLLISION_SPEED_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_SPEED_FWD_HPP_INCLUDED

#include <sanguis/collision/velocity_fwd.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sanguis
{
namespace collision
{

typedef
fcppt::math::vector::static_<
	sanguis::collision::velocity,
	2
>
speed;

}
}

#endif
