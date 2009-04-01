#include "factory.hpp"
#include "enemy.hpp"
#include "../property.hpp"
#include "../../damage_types.hpp"
#include "../../ai/simple.hpp"
#include "../../weapons/melee.hpp"
#include "../../weapons/pistol.hpp"
#include "../../../exception.hpp"
#include <sge/text.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::auto_ptr
sanguis::server::entities::enemies::create(
	enemy_type::type const etype,
	environment const &env,
	pos_type const &center,
	space_unit const direction,
	space_unit const angle)
{
	switch(etype) {
	case enemy_type::zombie00:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::list(
					static_cast<space_unit>(0)
				),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property_type::health,
					 entities::property(static_cast<space_unit>(3)))
					(entities::property_type::movement_speed,
					 entities::property(static_cast<space_unit>(20))),
				ai::ai_ptr(
					new ai::simple()),
				weapons::auto_ptr(
					new weapons::pistol(
						env,
						weapon_type::pistol,
						static_cast<time_type>(1),
						static_cast<space_unit>(1),
						static_cast<time_type>(0),
						3,
						static_cast<time_type>(15)
						)),
				1,
				static_cast<exp_type>(20)
				));
	case enemy_type::zombie01:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::list(
					static_cast<space_unit>(0)
				),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property_type::health,
					 entities::property(static_cast<space_unit>(3)))
					(entities::property_type::movement_speed,
					 entities::property(static_cast<space_unit>(20))),
				ai::ai_ptr(
					new ai::simple()),
				weapons::auto_ptr(
					new weapons::melee(
						env,
						static_cast<space_unit>(100), // range
						static_cast<time_type>(2), // cd
						static_cast<space_unit>(2) // damage
					)),
				1,
				static_cast<exp_type>(10)
				));
	case enemy_type::wolf_black:
	case enemy_type::wolf_brown:
	case enemy_type::wolf_white:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::list(
					static_cast<space_unit>(0)
				),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property_type::health,
					 entities::property(static_cast<space_unit>(1)))
					(entities::property_type::movement_speed,
					 entities::property(static_cast<space_unit>(80))),
				ai::ai_ptr(
					new ai::simple()),
				weapons::auto_ptr(
					new weapons::melee(
						env,
						static_cast<space_unit>(100), // range
						static_cast<time_type>(1), // cd
						static_cast<space_unit>(4) // damage
					)),
				1,
				static_cast<exp_type>(5)
			 ));
	case enemy_type::skeleton:
		return auto_ptr(
			new enemy(
			 etype,
			 env,
			 damage::list(
			 	static_cast<space_unit>(0)
			),
			 center,
			 angle,
			 direction,
			 boost::assign::map_list_of
				(entities::property_type::health,
				entities::property(static_cast<space_unit>(300)))
				(entities::property_type::movement_speed,
				entities::property(static_cast<space_unit>(40))),
			ai::ai_ptr(
				new ai::simple()),
			weapons::auto_ptr(
				new weapons::melee(
					env,
					static_cast<space_unit>(100), // range
					static_cast<time_type>(1), // cd
					static_cast<space_unit>(10) // damage
				)),
			 1,
			 static_cast<exp_type>(300)
			 ));
	case enemy_type::maggot:
		return auto_ptr(
			new enemy(
			 etype,
			 env,
			 damage::list(
			 	static_cast<space_unit>(0)
			),
			 center,
			 angle,
			 direction,
			 boost::assign::map_list_of
				(entities::property_type::health,
				entities::property(static_cast<space_unit>(1)))
				(entities::property_type::movement_speed,
				entities::property(static_cast<space_unit>(40))),
			ai::ai_ptr(
				new ai::simple()),
			weapons::auto_ptr(
				new weapons::melee(
				env,
				static_cast<space_unit>(100), // range
				static_cast<time_type>(1), // cd
				static_cast<space_unit>(0.5) // damage
				)),
			 1,
			 static_cast<exp_type>(1)
			 ));
	case enemy_type::spider:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::list(
					static_cast<space_unit>(0)
				),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property_type::health,
					 entities::property(static_cast<space_unit>(10)))
					(entities::property_type::movement_speed,
					 entities::property(static_cast<space_unit>(70))),
				ai::ai_ptr(
					new ai::simple()),
				weapons::auto_ptr(
					new weapons::melee(
						env,
						static_cast<space_unit>(120), // range
						static_cast<time_type>(2), // cd
						static_cast<space_unit>(5) // damage
					)),
				1,
				static_cast<exp_type>(15)
				));
	default:
		throw exception(
			SGE_TEXT("Invalid enemy_type in factory!"));
	}
}
