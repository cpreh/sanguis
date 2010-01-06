#include "virtual_to_screen.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::draw::sprite::point const
sanguis::client::draw2d::virtual_to_screen(
	sge::renderer::screen_size const &ss,
	messages::types::pos const &pos
)
{
	return fcppt::math::vector::structure_cast<
		sprite::point
	>(
		pos
	);
}

sanguis::draw::sprite::dim const
sanguis::client::draw2d::virtual_to_screen(
	sge::renderer::screen_size const &ss,
	messages::types::dim const &dim
)
{
	return fcppt::math::dim::structure_cast<
		sprite::dim
	>(
		dim
	);
}