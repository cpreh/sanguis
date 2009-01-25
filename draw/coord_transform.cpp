#include "coord_transform.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>

sge::sprite::point const
sanguis::virtual_to_screen(
	sge::renderer::screen_size_t const &ss,
	messages::pos_type const &pos)
{
	return sge::sprite::point(
		static_cast<sge::sprite::unit>(pos.x()),
		static_cast<sge::sprite::unit>(pos.y()));
}

sge::sprite::dim const
sanguis::virtual_to_screen(
	sge::renderer::screen_size_t const &ss,
	messages::dim_type const &dim)
{
	return sge::sprite::dim(static_cast<sge::sprite::unit>(dim.w()),
		static_cast<sge::sprite::unit>(dim.h()));
}

sanguis::messages::pos_type const
sanguis::screen_to_virtual(
	sge::renderer::screen_size_t const &ss,
	sge::sprite::point const &pos)
{
	return messages::pos_type(
		messages::mu(pos.x()),
		messages::mu(pos.y()));
}

sanguis::messages::dim_type const
sanguis::screen_to_virtual(
	sge::renderer::screen_size_t const &ss,
	sge::sprite::dim const &dim)
{
	return messages::dim_type(
		messages::mu(dim.w()),
		messages::mu(dim.h()));
}
