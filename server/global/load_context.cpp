#include "load_context.hpp"
#include "../../load/context_base.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

sanguis::server::global::load_context::load_context(
	load::context_base const &_model_context
)
:
	model_context_(_model_context)
{}

sanguis::server::dim_type const
sanguis::server::global::load_context::entity_dim(
	string const &_model_name
) const
{
	return
		fcppt::math::dim::structure_cast<
			dim_type
		>(
			model_context_.model_dim(
				_model_name
			)
		);
}
