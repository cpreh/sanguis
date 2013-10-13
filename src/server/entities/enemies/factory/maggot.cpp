#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/factory/maggot.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::maggot(
	sanguis::server::entities::enemies::factory::parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::entities::enemies::enemy
		>(
			_parameters.diff_clock(),
			_parameters.enemy_type(),
			_parameters.load_context(),
			sanguis::server::damage::no_armor(),
			sanguis::server::health(
				2.f
				*
				_parameters.difficulty().get()
			),
			sanguis::server::entities::movement_speed(
				40.f
			),
			sanguis::server::ai::create_simple(
				sanguis::server::ai::sight_range(
					1000.f
				)
			),
			fcppt::make_unique_ptr<
				sanguis::server::weapons::melee
			>(
				_parameters.diff_clock(),
				sanguis::server::weapons::range(
					75.f
				),
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						1.f
					)
				),
				sanguis::server::weapons::damage(
					0.5f
				)
			),
			sanguis::server::pickup_probability(
				0.1f
			),
			sanguis::server::exp(
				1.f
			),
			_parameters.difficulty(),
			_parameters.spawn_owner(),
			sanguis::server::auras::container()
		);
}
