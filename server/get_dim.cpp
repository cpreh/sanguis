#include "get_dim.hpp"
#include "../load/model/context.hpp"
#include "../load/model/collection.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/structure_cast.hpp>
#include <sge/text.hpp>

sanguis::server::dim_type const
sanguis::server::get_dim(
	load::model::context const &ctx,
	sge::string const &model,
	sge::string const &part)
{
	return sge::structure_cast<dim_type>(
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
