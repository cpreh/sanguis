#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/server/ai/idle.hpp>
#include <sanguis/server/ai/stop.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/weapons/optional_target.hpp>


void
sanguis::server::ai::idle(
	sanguis::server::entities::with_ai &_me
)
{
	_me.use_weapon(
		false,
		sanguis::is_primary_weapon(
			true
		)
	);

	_me.use_weapon(
		false,
		sanguis::is_primary_weapon(
			false
		)
	);

	_me.target(
		sanguis::server::weapons::optional_target()
	);

	sanguis::server::ai::stop(
		_me
	);
}
