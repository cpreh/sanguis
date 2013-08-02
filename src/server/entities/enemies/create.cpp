#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_simple_without_owner.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/spawn_owner_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::create(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::creator::enemy_type const _etype,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::entities::enemies::spawn_owner const &_spawn
)
{
	switch(
		_etype
	)
	{
	case sanguis::creator::enemy_type::zombie00:
		return
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::enemy
			>(
				_diff_clock,
				_random_generator,
				_etype,
				_load_context,
				sanguis::server::damage::no_armor(),
				sanguis::server::health(9.f),
				sanguis::server::entities::movement_speed(0.5f),
				sanguis::server::ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				fcppt::make_unique_ptr<
					sanguis::server::weapons::pistol
				>(
					_diff_clock,
					sanguis::weapon_type::pistol,
					sanguis::server::weapons::base_cooldown(
						sanguis::duration_second(
							1.f
						)
					),
					sanguis::server::weapons::damage(1.f),
					sanguis::server::weapons::cast_point(
						sanguis::duration_second(
							0
						)
					),
					sanguis::server::weapons::magazine_size(3u),
					sanguis::server::weapons::reload_time(
						sanguis::duration_second(
							15.f
						)
					),
					sanguis::server::weapons::range(20.f)
				),
				sanguis::server::pickup_probability(0.25f),
				sanguis::server::exp(10.f),
				_spawn
			);
	case sanguis::creator::enemy_type::zombie01:
		return
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::enemy
			>(
				_diff_clock,
				_random_generator,
				_etype,
				_load_context,
				sanguis::server::damage::no_armor(),
				sanguis::server::health(3.f),
				sanguis::server::entities::movement_speed(0.4f),
				sanguis::server::ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				fcppt::make_unique_ptr<
					sanguis::server::weapons::melee
				>(
					_diff_clock,
					sanguis::server::weapons::range(1.5f),
					sanguis::server::weapons::base_cooldown(
						sanguis::duration_second(
							2.f
						)
					),
					sanguis::server::weapons::damage(2.f)
				),
				sanguis::server::pickup_probability(0.25f),
				sanguis::server::exp(5.f),
				_spawn
			);
	case sanguis::creator::enemy_type::wolf_black:
	case sanguis::creator::enemy_type::wolf_brown:
	case sanguis::creator::enemy_type::wolf_white:
		return
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::enemy
			>(
				_diff_clock,
				_random_generator,
				_etype,
				_load_context,
				sanguis::server::damage::no_armor(),
				sanguis::server::health(3.f),
				sanguis::server::entities::movement_speed(1.7f),
				sanguis::server::ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				fcppt::make_unique_ptr<
					sanguis::server::weapons::melee
				>(
					_diff_clock,
					sanguis::server::weapons::range(1.5f),
					sanguis::server::weapons::base_cooldown(
						sanguis::duration_second(
							1.f
						)
					),
					sanguis::server::weapons::damage(4.f)
				),
				sanguis::server::pickup_probability(0.25f),
				sanguis::server::exp(10.f),
				_spawn
			);
	case sanguis::creator::enemy_type::skeleton:
		return
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::enemy
			>(
				_diff_clock,
				_random_generator,
				_etype,
				_load_context,
				sanguis::server::damage::no_armor(),
				sanguis::server::health(500.f),
				sanguis::server::entities::movement_speed(1.f),
				sanguis::server::ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				fcppt::make_unique_ptr<
					sanguis::server::weapons::melee
				>(
					_diff_clock,
					sanguis::server::weapons::range(2.f),
					sanguis::server::weapons::base_cooldown(
						sanguis::duration_second(
							1.f
						)
					),
					sanguis::server::weapons::damage(10.f)
				),
				sanguis::server::pickup_probability(0.75f),
				sanguis::server::exp(300.f),
				_spawn
			);
	case sanguis::creator::enemy_type::maggot:
		return
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::enemy
			>(
				_diff_clock,
				_random_generator,
				_etype,
				_load_context,
				sanguis::server::damage::no_armor(),
				sanguis::server::health(1.f),
				sanguis::server::entities::movement_speed(0.8f),
				sanguis::server::ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				fcppt::make_unique_ptr<
					sanguis::server::weapons::melee
				>(
					_diff_clock,
					sanguis::server::weapons::range(1.5f),
					sanguis::server::weapons::base_cooldown(
						sanguis::duration_second(
							1.f
						)
					),
					sanguis::server::weapons::damage(0.5f)
				),
				sanguis::server::pickup_probability(0.1f),
				sanguis::server::exp(1.f),
				_spawn
			);
	case sanguis::creator::enemy_type::spider:
		return
			fcppt::make_unique_ptr<
				sanguis::server::entities::enemies::enemy
			>(
				_diff_clock,
				_random_generator,
				_etype,
				_load_context,
				sanguis::server::damage::no_armor(),
				sanguis::server::health(12.f),
				sanguis::server::entities::movement_speed(1.5f),
				sanguis::server::ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				fcppt::make_unique_ptr<
					sanguis::server::weapons::melee
				>(
					_diff_clock,
					sanguis::server::weapons::range(1.5f),
					sanguis::server::weapons::base_cooldown(
						sanguis::duration_second(
							2.f
						)
					),
					sanguis::server::weapons::damage(5.f)
				),
				sanguis::server::pickup_probability(0.5f),
				sanguis::server::exp(12.f),
				_spawn
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
