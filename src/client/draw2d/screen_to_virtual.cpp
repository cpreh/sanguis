#include "screen_to_virtual.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::messages::types::vector2 const
sanguis::client::draw2d::screen_to_virtual(
	sprite::point const &_point
)
{
	return
		fcppt::math::vector::structure_cast<
			messages::types::vector2
		>(
			_point
		);
}
