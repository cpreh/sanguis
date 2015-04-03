#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_COLLIDES_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_COLLIDES_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
{
namespace simple
{

template<
	typename Type1,
	typename Type2
>
inline
bool
collides(
	Type1 const &_left,
	Type2 const &_right
)
{
	return
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
