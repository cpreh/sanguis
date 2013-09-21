#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/zombie01.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::zombie01(
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
				3.f
			),
			sanguis::server::entities::movement_speed(
				20.f
			),
			sanguis::server::ai::create_simple(
				_parameters.diff_clock(),
				_parameters.random_generator()
			),
			fcppt::make_unique_ptr<
				sanguis::server::weapons::melee
			>(
				_parameters.diff_clock(),
				sanguis::server::weapons::range(
					1.5f
				),
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						2.f
					)
				),
				sanguis::server::weapons::damage(
					2.f
				)
			),
			sanguis::server::pickup_probability(
				0.25f
			),
			sanguis::server::exp(
				5.f
			),
			_parameters.difficulty(),
			_parameters.spawn_owner()
		);
}
