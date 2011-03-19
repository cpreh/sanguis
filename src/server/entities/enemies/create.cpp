#include "create.hpp"
#include "enemy.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../weapons/melee.hpp"
#include "../../weapons/pistol.hpp"
#include "../../weapons/unique_ptr.hpp"
#include "../../ai/create_simple.hpp"
#include "../../../exception.hpp"
#include <fcppt/container/map_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sanguis::server::entities::unique_ptr
sanguis::server::entities::enemies::create(
	enemy_type::type const _etype,
	environment::load_context_ptr const _load_context,
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
				_etype,
				_load_context,
				damage::no_armor(),
				health_type(9),
				movement_speed(25),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::pistol
					>(
						weapon_type::pistol,
						weapons::base_cooldown(1),
						weapons::damage(1),
						weapons::cast_point(0),
						weapons::magazine_size(3),
						weapons::reload_time(15),
						weapons::range(1000)
					)
				),
				static_cast<probability_type>(0.25),
				static_cast<exp_type>(10),
				_spawn
			)
		);
	case enemy_type::zombie01:
		return unique_ptr(
			new enemy(
//			fcppt::make_unique_ptr<
//				enemy
//			>(
				_etype,
				_load_context,
				damage::no_armor(),
				health_type(3),
				movement_speed(20),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(75),
						weapons::base_cooldown(2),
						weapons::damage(2)
					)
				),
				static_cast<probability_type>(0.25),
				static_cast<exp_type>(5),
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
				_etype,
				_load_context,
				damage::no_armor(),
				health_type(3),
				movement_speed(85),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(75),
						weapons::base_cooldown(1),
						weapons::damage(4)
					)
				),
				static_cast<probability_type>(0.25),
				static_cast<exp_type>(10),
				_spawn
			)
		);
	case enemy_type::skeleton:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_etype,
				_load_context,
				damage::no_armor(),
				health_type(500),
				movement_speed(50),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(100),
						weapons::base_cooldown(1),
						weapons::damage(10)
					)
				),
				static_cast<probability_type>(0.75),
				static_cast<exp_type>(300),
				_spawn
			)
		);
	case enemy_type::maggot:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_etype,
				_load_context,
				damage::no_armor(),
				health_type(1),
				movement_speed(40),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(75),
						weapons::base_cooldown(1),
						weapons::damage(0.5f)
					)
				),
				static_cast<probability_type>(0.1),
				static_cast<exp_type>(1),
				_spawn
			)
		);
	case enemy_type::spider:
		return unique_ptr(
			new enemy(
			//fcppt::make_unique_ptr<
			//	enemy
			//>(
				_etype,
				_load_context,
				damage::no_armor(),
				health_type(12),
				movement_speed(75),
				ai::create_simple(),
				weapons::unique_ptr(
					fcppt::make_unique_ptr<
						weapons::melee
					>(
						weapons::range(75),
						weapons::base_cooldown(2),
						weapons::damage(5)
					)
				),
				static_cast<probability_type>(0.5),
				static_cast<exp_type>(12),
				_spawn
			)		
		);
	case enemy_type::size:
		break;
	}

	throw exception(
		FCPPT_TEXT("Invalid enemy_type in factory!")
	);
}
