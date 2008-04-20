#include "get_dim.hpp"
#include "../load/model/singleton.hpp"
#include "../load/model/collection.hpp"

sanguis::messages::dim_type
sanguis::server::get_dim(
	sge::string const &model,
	sge::string const &part)
{
	return sge::math::structure_cast<messages::space_unit>(
		load::model::singleton()
			[model]
			[part]
			[weapon_type::none]
			[animation_type::none]
		.get().dim());
}
