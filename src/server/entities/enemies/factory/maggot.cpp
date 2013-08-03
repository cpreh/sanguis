#include <sanguis/duration_second.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple_without_owner.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/scale_difficulty.hpp>
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
			_parameters.random_generator(),
			_parameters.enemy_type(),
			_parameters.load_context(),
			sanguis::server::damage::no_armor(),
			sanguis::server::health(
				sanguis::server::entities::enemies::scale_difficulty(
					2.f,
					_parameters.difficulty()
				)
			),
			sanguis::server::entities::movement_speed(
				0.8f
			),
			sanguis::server::ai::create_simple_without_owner(
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
			_parameters.spawn_owner()
		);
}
