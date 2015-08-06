#ifndef SANGUIS_COLLISION_IMPL_WORLD_COLLIDES_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_COLLIDES_HPP_INCLUDED

#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <fcppt/boost_units_value.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/map.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
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
		// TODO: Can we do this on boost::units directly?
		fcppt::math::vector::length(
			fcppt::math::vector::map(
				_left.center().get()
				-
				_right.center().get()
				,
				fcppt::boost_units_value{}
			)
		)
		<=
		(
			_left.radius().get()
			+
			_right.radius().get()
		).value()
		;
}

}
}
}
}

#endif
