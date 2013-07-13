#include <sanguis/entity_id.hpp>
#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/load/server_context.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/global/load_context.hpp>
#include <sanguis/server/global/next_id_callback.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sanguis::server::global::load_context::load_context(
	sanguis::load::server_context const &_model_context,
	sanguis::server::global::next_id_callback const &_next_id_callback
)
:
	sanguis::server::environment::load_context(),
	model_context_(
		_model_context
	),
	next_id_callback_(
		_next_id_callback
	)
{
}

sanguis::server::global::load_context::~load_context()
{
}

sanguis::server::dim const
sanguis::server::global::load_context::entity_dim(
	sanguis::server::model_name const &_model_name
) const
{
	return
		fcppt::math::dim::structure_cast<
			sanguis::server::dim
		>(
			model_context_.model_dim(
				_model_name.get()
			)
		)
		/
		static_cast<
			sanguis::server::space_unit
		>(
			sanguis::pixels_per_meter()
		);
}

sanguis::entity_id const
sanguis::server::global::load_context::next_id() const
{
	return
		next_id_callback_();
}
