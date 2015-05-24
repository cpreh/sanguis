#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/destructible.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/difficulty_value.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/make_destructible.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/int_to_float.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::world::make_destructible(
	sanguis::creator::destructible_type const _destructible_type,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::world::difficulty const _difficulty
)
{
	sanguis::server::entities::enemies::difficulty const difficulty(
		fcppt::cast::int_to_float<
			sanguis::server::entities::enemies::difficulty_value
		>(
			_difficulty.get()
		)
		*
		fcppt::literal<
			sanguis::server::entities::enemies::difficulty_value
		>(
			5
		)
	);

	return
		fcppt::unique_ptr_to_base<
			sanguis::server::entities::base
		>(
			fcppt::make_unique_ptr_fcppt<
				sanguis::server::entities::destructible
			>(
				_destructible_type,
				_load_context,
				sanguis::server::health(
					1.f
					*
					difficulty.get()
				),
				sanguis::server::damage::no_armor(),
				difficulty
			)
		);
}
