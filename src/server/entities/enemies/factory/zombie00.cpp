#include <sanguis/duration_second.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple_without_owner.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/entities/enemies/factory/zombie00.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::factory::zombie00(
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
				9.f
			),
			sanguis::server::entities::movement_speed(
				0.5f
			),
			sanguis::server::ai::create_simple_without_owner(
				_parameters.diff_clock(),
				_parameters.random_generator()
			),
			fcppt::make_unique_ptr<
				sanguis::server::weapons::pistol
			>(
				_parameters.diff_clock(),
				sanguis::weapon_type::pistol,
				sanguis::server::weapons::base_cooldown(
					sanguis::duration_second(
						1.f
					)
				),
				sanguis::server::weapons::damage(
					1.f
				),
				sanguis::server::weapons::cast_point(
					sanguis::duration_second(
						0
					)
				),
				sanguis::server::weapons::magazine_size(
					3u
				),
				sanguis::server::weapons::reload_time(
					sanguis::duration_second(
						15.f
					)
				),
				sanguis::server::weapons::range(
					20.f
				)
			),
			sanguis::server::pickup_probability(
				0.25f
			),
			sanguis::server::exp(
				10.f
			),
			_parameters.spawn_owner()
		);
}
