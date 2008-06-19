#include "coord_transform.hpp"

sge::sprite::point const sanguis::virtual_to_screen(const sge::renderer::screen_size_t &ss,const messages::pos_type &pos)
{
	return sge::sprite::point(
		static_cast<sge::sprite::unit>(pos.x()),
		static_cast<sge::sprite::unit>(pos.y()));
}

sge::sprite::dim const sanguis::virtual_to_screen(const sge::renderer::screen_size_t &ss,const messages::dim_type &dim)
{
	return sge::sprite::dim(static_cast<sge::sprite::unit>(dim.w()),
		static_cast<sge::sprite::unit>(dim.h()));
}

sanguis::messages::pos_type const sanguis::screen_to_virtual(const sge::renderer::screen_size_t &ss,const sge::sprite::point &pos)
{
	return messages::pos_type(
		messages::mu(pos.x()),
		messages::mu(pos.y()));
}

sanguis::messages::dim_type const sanguis::screen_to_virtual(const sge::renderer::screen_size_t &ss,const sge::sprite::dim &dim)
{
	return messages::dim_type(
		messages::mu(dim.w()),
		messages::mu(dim.h()));
}
