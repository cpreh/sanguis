#include "factory.hpp"
#include "enemy.hpp"
#include "../property.hpp"
#include "../../damage/no_armor.hpp"
#include "../../damage/list.hpp"
#include "../../ai/simple.hpp"
#include "../../weapons/melee.hpp"
#include "../../weapons/pistol.hpp"
#include "../../../exception.hpp"
#include <sge/container/map_impl.hpp>
#include <sge/text.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::auto_ptr
sanguis::server::entities::enemies::create(
	enemy_type::type const etype,
	environment::object_ptr const env,
	pos_type const &center,
	space_unit const direction,
	space_unit const angle
)
{
	switch(etype) {
	case enemy_type::zombie00:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::no_armor(),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(
						entities::property_type::health,
						entities::property(
							static_cast<space_unit>(9)
						)
					)
					(
						entities::property_type::movement_speed,
						entities::property(
							static_cast<space_unit>(25)
						)
					),
				ai::auto_ptr(
					new ai::simple()
				),
				weapons::auto_ptr(
					new weapons::pistol(
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
				static_cast<exp_type>(10)
			)
		);
	case enemy_type::zombie01:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::no_armor(),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property_type::health,
					 entities::property(static_cast<space_unit>(3)))
					(entities::property_type::movement_speed,
					 entities::property(static_cast<space_unit>(20))),
				ai::auto_ptr(
					new ai::simple()),
				weapons::auto_ptr(
					new weapons::melee(
						weapons::range(75),
						weapons::base_cooldown(2),
						weapons::damage(2)
					)
				),
				static_cast<probability_type>(0.25),
				static_cast<exp_type>(5)
			)
		);
	case enemy_type::wolf_black:
	case enemy_type::wolf_brown:
	case enemy_type::wolf_white:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::no_armor(),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property_type::health,
					 entities::property(static_cast<space_unit>(3)))
					(entities::property_type::movement_speed,
					 entities::property(static_cast<space_unit>(85))),
				ai::auto_ptr(
					new ai::simple()),
				weapons::auto_ptr(
					new weapons::melee(
						weapons::range(75),
						weapons::base_cooldown(1),
						weapons::damage(4)
					)
				),
				static_cast<probability_type>(0.25),
				static_cast<exp_type>(10)
			)
		);
	case enemy_type::skeleton:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::no_armor(),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property_type::health,
					entities::property(static_cast<space_unit>(500)))
					(entities::property_type::movement_speed,
					entities::property(static_cast<space_unit>(50))),
				ai::auto_ptr(
					new ai::simple()
				),
				weapons::auto_ptr(
					new weapons::melee(
						weapons::range(100),
						weapons::base_cooldown(1),
						weapons::damage(10)
					)
				),
				static_cast<probability_type>(0.75),
				static_cast<exp_type>(300)
			)
		);
	case enemy_type::maggot:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::no_armor(),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property_type::health,
					entities::property(static_cast<space_unit>(1)))
					(entities::property_type::movement_speed,
					entities::property(static_cast<space_unit>(40))),
				ai::auto_ptr(
					new ai::simple()
				),
				weapons::auto_ptr(
					new weapons::melee(
						weapons::range(75),
						weapons::base_cooldown(1),
						weapons::damage(0.5f)
					)
				),
				static_cast<probability_type>(0.1),
				static_cast<exp_type>(1)
			)
		);
	case enemy_type::spider:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::no_armor(),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property_type::health,
					 entities::property(static_cast<space_unit>(12)))
					(entities::property_type::movement_speed,
					 entities::property(static_cast<space_unit>(75))),
				ai::auto_ptr(
					new ai::simple()
				),
				weapons::auto_ptr(
					new weapons::melee(
						weapons::range(75),
						weapons::base_cooldown(2),
						weapons::damage(5)
					)
				),
				static_cast<probability_type>(0.5),
				static_cast<exp_type>(12)
			)		
		);
	default:
		throw exception(
			SGE_TEXT("Invalid enemy_type in factory!"));
	}
}
