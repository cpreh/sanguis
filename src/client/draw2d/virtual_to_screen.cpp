#include "virtual_to_screen.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::virtual_to_screen(
	messages::types::vector2 const &_vec
)
{
	return
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			_vec
		);
}
