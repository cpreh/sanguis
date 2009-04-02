#include "coord_transform.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/structure_cast.hpp>

sge::sprite::point const
sanguis::virtual_to_screen(
	sge::renderer::screen_size const &ss,
	messages::types::pos const &pos)
{
	return sge::structure_cast<
		sge::sprite::point
	>(
		pos
	);
}

sge::sprite::dim const
sanguis::virtual_to_screen(
	sge::renderer::screen_size const &ss,
	messages::types::dim const &dim)
{
	return sge::structure_cast<
		sge::sprite::dim
	>(
		dim
	);
}

sanguis::messages::types::pos const
sanguis::screen_to_virtual(
	sge::renderer::screen_size const &ss,
	sge::sprite::point const &pos)
{
	return sge::structure_cast<
		messages::types::pos
	>(
		pos
	);
}

sanguis::messages::types::dim const
sanguis::screen_to_virtual(
	sge::renderer::screen_size const &ss,
	sge::sprite::dim const &dim)
{
	return sge::structure_cast<
		messages::types::dim
	>(
		dim
	);
}
