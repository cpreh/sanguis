#include <sanguis/entity_id.hpp>
#include <sanguis/model/cell_size.hpp>
#include <sanguis/server/load.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/model_size.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/global/load_context.hpp>
#include <sanguis/server/global/next_id_callback.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sanguis::server::global::load_context::load_context(
	sanguis::server::load const &_model_context,
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

sanguis::server::model_size const
sanguis::server::global::load_context::model_size(
	sanguis::server::model_name const &_model_name
) const
{
	return
		sanguis::server::model_size(
			fcppt::math::dim::structure_cast<
				sanguis::server::model_size::value_type
			>(
				model_context_.model_dim(
					_model_name.get()
				).get()
			)
		);
}

sanguis::entity_id const
sanguis::server::global::load_context::next_id()
{
	return
		next_id_callback_();
}
