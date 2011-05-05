#include "load_context.hpp"
#include "../space_unit.hpp"
#include "../../load/context_base.hpp"
#include "../../pixels_per_meter.hpp"
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

sanguis::server::global::load_context::load_context(
	load::context_base const &_model_context
)
:
	model_context_(_model_context)
{
}

sanguis::server::global::load_context::~load_context()
{
}

sanguis::server::dim const
sanguis::server::global::load_context::entity_dim(
	string const &_model_name
) const
{
	return
		fcppt::math::dim::structure_cast<
			server::dim
		>(
			model_context_.model_dim(
				_model_name
			)
		)
		/
		static_cast<
			server::space_unit
		>(
			sanguis::pixels_per_meter()
		);
}
