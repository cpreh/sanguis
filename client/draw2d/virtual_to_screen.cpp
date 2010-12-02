#include "virtual_to_screen.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::client::draw2d::sprite::point const
sanguis::client::draw2d::virtual_to_screen(
	sge::renderer::screen_size const &_screen_size,
	messages::types::pos const &_pos
)
{
	return
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			_pos
		);
}

sanguis::client::draw2d::sprite::dim const
sanguis::client::draw2d::virtual_to_screen(
	sge::renderer::screen_size const &_screen_size,
	messages::types::dim const &_dim
)
{
	return
		fcppt::math::dim::structure_cast<
			sprite::dim
		>(
			_dim
		);
}
