#include "screen_to_virtual.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::messages::types::pos const
sanguis::client::draw2d::screen_to_virtual(
	sge::renderer::screen_size const &_screen_size,
	sprite::point const &_pos
)
{
	return
		fcppt::math::vector::structure_cast<
			messages::types::pos
		>(
			_pos
		);
}

sanguis::messages::types::dim const
sanguis::client::draw2d::screen_to_virtual(
	sge::renderer::screen_size const &_screen_size,
	sprite::dim const &_dim
)
{
	return
		fcppt::math::dim::structure_cast<
			messages::types::dim
		>(
			_dim
		);
}
