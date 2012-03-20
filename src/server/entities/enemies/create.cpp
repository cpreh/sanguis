#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/damage/no_armor.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/weapons/melee.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/ai/create_simple_without_owner.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::create(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	enemy_type::type const _etype,
	environment::load_context &_load_context,
	entities::auto_weak_link const _spawn
)
{
	switch(
		_etype
	)
	{
	case enemy_type::zombie00:
		return entities::unique_ptr(
			new enemy(
//			fcppt::make_unique_ptr<
//				enemy
//			>(
				_diff_clock,
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(9.f),
				movement_speed(0.5f),
				ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::pistol
					>(
						fcppt::cref(
							_diff_clock
						),
						weapon_type::pistol,
						weapons::base_cooldown(
							sanguis::duration_second(
								1.f
							)
						),
						weapons::damage(1.f),
						weapons::cast_point(
							sanguis::duration_second(
								0
							)
						),
						weapons::magazine_size(3u),
						weapons::reload_time(
							sanguis::duration_second(
								15.f
							)
						),
						weapons::range(20.f)
					)
				),
				server::probability(0.25f),
				server::exp(10.f),
				_spawn
			)
		);
	case enemy_type::zombie01:
		return unique_ptr(
			new enemy(
//			fcppt::make_unique_ptr<
//				enemy
//			>(
				_diff_clock,
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(3.f),
				movement_speed(0.4f),
				ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						fcppt::cref(
							_diff_clock
						),
						weapons::range(1.5f),
						weapons::base_cooldown(
							sanguis::duration_second(
								2.f
							)
						),
						weapons::damage(2.f)
					)
				),
				server::probability(0.25f),
				server::exp(5.f),
				_spawn
			)
		);
	case enemy_type::wolf_black:
	case enemy_type::wolf_brown:
	case enemy_type::wolf_white:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_diff_clock,
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(3.f),
				movement_speed(1.7f),
				ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						fcppt::cref(
							_diff_clock
						),
						weapons::range(1.5f),
						weapons::base_cooldown(
							sanguis::duration_second(
								1.f
							)
						),
						weapons::damage(4.f)
					)
				),
				server::probability(0.25f),
				server::exp(10.f),
				_spawn
			)
		);
	case enemy_type::skeleton:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_diff_clock,
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(500.f),
				movement_speed(1.f),
				ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						fcppt::cref(
							_diff_clock
						),
						weapons::range(2.f),
						weapons::base_cooldown(
							sanguis::duration_second(
								1.f
							)
						),
						weapons::damage(10.f)
					)
				),
				server::probability(0.75f),
				server::exp(300.f),
				_spawn
			)
		);
	case enemy_type::maggot:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_diff_clock,
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(1.f),
				movement_speed(0.8f),
				ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						fcppt::cref(
							_diff_clock
						),
						weapons::range(1.5f),
						weapons::base_cooldown(
							sanguis::duration_second(
								1.f
							)
						),
						weapons::damage(0.5f)
					)
				),
				server::probability(0.1f),
				server::exp(1.f),
				_spawn
			)
		);
	case enemy_type::spider:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_diff_clock,
				_etype,
				_load_context,
				damage::no_armor(),
				server::health(12.f),
				movement_speed(1.5f),
				ai::create_simple_without_owner(
					_diff_clock,
					_random_generator
				),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						fcppt::cref(
							_diff_clock
						),
						weapons::range(1.5f),
						weapons::base_cooldown(
							sanguis::duration_second(
								2.f
							)
						),
						weapons::damage(5.f)
					)
				),
				server::probability(0.5f),
				server::exp(12.f),
				_spawn
			)
		);
	case enemy_type::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
