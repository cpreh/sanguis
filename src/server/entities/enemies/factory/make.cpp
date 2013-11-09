#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/make.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::make(
	sanguis::server::entities::enemies::factory::parameters const &_parameters,
	sanguis::server::damage::armor const &_armor,
	sanguis::server::health const _health,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::ai::create_function const &_ai_create_function,
	sanguis::server::weapons::unique_ptr &&_weapon,
	sanguis::server::pickup_probability const _pickup_probability,
	sanguis::server::exp const _exp,
	sanguis::server::auras::container &&_auras
)
{
	sanguis::server::entities::enemies::parameters parameters(
		_parameters.diff_clock(),
		_parameters.enemy_type(),
		_parameters.load_context(),
		_armor,
		_health,
		_movement_speed,
		_ai_create_function,
		std::move(
			_weapon
		),
		_pickup_probability,
		_exp,
		_parameters.difficulty(),
		_parameters.spawn_owner(),
		std::move(
			_auras
		)
	);

	// TODO: Create special enemies here as well!
	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::enemy
		>(
			std::move(
				parameters
			)
		);
}
