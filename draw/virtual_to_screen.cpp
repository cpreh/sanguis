#include "virtual_to_screen.hpp"

sge::sprite_point sanguis::virtual_to_screen(const sge::screen_size_t &ss,const messages::pos_type &pos)
{
	return sge::sprite_point(
		static_cast<sge::sprite_unit>(pos.x() * static_cast<messages::pos_type::value_type>(ss.w())),
		static_cast<sge::sprite_unit>(pos.y() * static_cast<messages::pos_type::value_type>(ss.w())));
}

sge::sprite_dim sanguis::virtual_to_screen(const sge::screen_size_t &ss,const messages::dim_type &dim)
{
	return sge::sprite_dim(
		static_cast<sge::sprite_unit>(dim.w() * static_cast<messages::pos_type::value_type>(ss.w())),
		static_cast<sge::sprite_unit>(dim.h() * static_cast<messages::pos_type::value_type>(ss.w())));
}


