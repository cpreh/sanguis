#include "coord_transform.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/structure_cast.hpp>

sanguis::draw::sprite::point const
sanguis::virtual_to_screen(
	sge::renderer::screen_size const &ss,
	messages::types::pos const &pos
)
{
	return sge::math::vector::structure_cast<
		sprite::point
	>(
		pos
	);
}

sanguis::draw::sprite::dim const
sanguis::virtual_to_screen(
	sge::renderer::screen_size const &ss,
	messages::types::dim const &dim
)
{
	return sge::math::dim::structure_cast<
		sprite::dim
	>(
		dim
	);
}

sanguis::messages::types::pos const
sanguis::screen_to_virtual(
	sge::renderer::screen_size const &ss,
	sprite::point const &pos
)
{
	return sge::math::vector::structure_cast<
		messages::types::pos
	>(
		pos
	);
}

sanguis::messages::types::dim const
sanguis::screen_to_virtual(
	sge::renderer::screen_size const &ss,
	sprite::dim const &dim
)
{
	return sge::math::dim::structure_cast<
		messages::types::dim
	>(
		dim
	);
}
