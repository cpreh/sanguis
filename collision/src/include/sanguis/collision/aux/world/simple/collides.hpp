#ifndef SANGUIS_COLLISION_AUX_WORLD_SIMPLE_COLLIDES_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_WORLD_SIMPLE_COLLIDES_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/aux/world/simple/groups_collide.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{
namespace world
{
namespace simple
{

template<
	typename Type1,
	typename Type2
>
bool
collides(
	Type1 const &_left,
	Type2 const &_right
)
{
	return
		sanguis::collision::aux::world::simple::groups_collide(
			_left.collision_groups(),
			_right.collision_groups()
		)
		&&
		fcppt::math::vector::length(
			_left.center().get()
			-
			_right.center().get()
		)
		<=
		_left.radius().get()
		+
		_right.radius().get()
		;
}

}
}
}
}
}

#endif
