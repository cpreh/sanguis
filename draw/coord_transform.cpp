#include "coord_transform.hpp"

sge::sprite::point sanguis::virtual_to_screen(const sge::screen_size_t &ss,const messages::pos_type &pos)
{
	return sge::sprite::point(
		static_cast<sge::sprite::unit>(pos.x() * static_cast<messages::pos_type::value_type>(ss.w())),
		static_cast<sge::sprite::unit>(pos.y() * static_cast<messages::pos_type::value_type>(ss.w())));
}

sge::sprite::dim sanguis::virtual_to_screen(const sge::screen_size_t &ss,const messages::dim_type &dim)
{
	return sge::sprite::dim(
		static_cast<sge::sprite::unit>(dim.w() * static_cast<messages::pos_type::value_type>(ss.w())),
		static_cast<sge::sprite::unit>(dim.h() * static_cast<messages::pos_type::value_type>(ss.w())));
}

sanguis::messages::pos_type sanguis::screen_to_virtual(const sge::screen_size_t &ss,const sge::sprite::point &pos)
{
	return messages::pos_type(
		static_cast<messages::space_unit>(pos.x())/static_cast<messages::space_unit>(ss.w()),
		static_cast<messages::space_unit>(pos.y())/static_cast<messages::space_unit>(ss.w())
		);
}

sanguis::messages::dim_type sanguis::screen_to_virtual(const sge::screen_size_t &ss,const sge::sprite::dim &dim)
{
	return messages::dim_type(
		static_cast<messages::space_unit>(dim.w())/static_cast<messages::space_unit>(ss.w()),
		static_cast<messages::space_unit>(dim.h())/static_cast<messages::space_unit>(ss.w())
		);
}
