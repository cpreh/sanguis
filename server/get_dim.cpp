#include "get_dim.hpp"
#include "../load/model/context.hpp"
#include "../load/model/collection.hpp"
#include <sge/text.hpp>

sanguis::server::dim_type const
sanguis::server::get_dim(
	load::model::context const &ctx,
	sge::string const &model,
	sge::string const &part)
{
	return sge::math::structure_cast<space_unit>(
		ctx()
			[model]
			[part]
			[weapon_type::none]
			[animation_type::none]
		.get().dim());
}

sanguis::server::dim_type const
sanguis::server::default_dim(
	load::model::context const &ctx,
	sge::string const &model)
{
	return get_dim(
		ctx,
		model,
		SGE_TEXT("default"));
}
