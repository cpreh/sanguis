#ifndef SANGUIS_COLLISION_IMPL_COLLIDES_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_COLLIDES_HPP_INCLUDED

#include <sanguis/collision/impl/circle.hpp>
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

inline
bool
collides(
	sanguis::collision::impl::circle const _left,
	sanguis::collision::impl::circle const _right
)
{
	return
		// TODO: Can we do this on boost::units directly?
		fcppt::math::vector::length(
			fcppt::math::vector::map(
				_left.origin()
				-
				_right.origin()
				,
				fcppt::boost_units_value{}
			)
		)
		<=
		(
			_left.radius()
			+
			_right.radius()
		).value()
		;
}

}
}
}

#endif
