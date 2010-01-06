#include "screen_to_virtual.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>

sanguis::messages::types::pos const
sanguis::client::draw2d::screen_to_virtual(
	sge::renderer::screen_size const &ss,
	sprite::point const &pos
)
{
	return fcppt::math::vector::structure_cast<
		messages::types::pos
	>(
		pos
	);
}

sanguis::messages::types::dim const
sanguis::client::draw2d::screen_to_virtual(
	sge::renderer::screen_size const &ss,
	sprite::dim const &dim
)
{
	return fcppt::math::dim::structure_cast<
		messages::types::dim
	>(
		dim
	);
}
