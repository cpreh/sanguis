#include "default_dim.hpp"
#include "../load/model/context.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/model.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/structure_cast.hpp>

sanguis::server::dim_type const
sanguis::server::default_dim(
	load::model::context const &ctx,
	sge::string const &model)
{
	return sge::math::dim::structure_cast<
		dim_type
	>(
		ctx()
			[model].
			dim()
	);
}
