#include "factory.hpp"
#include "enemy.hpp"
#include "../../damage_types.hpp"
#include "../../ai/simple.hpp"
#include "../../weapons/melee.hpp"
#include "../../../exception.hpp"
#include <sge/text.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::auto_ptr
sanguis::server::entities::enemies::create(
	enemy_type::type const etype,
	environment const &env,
	messages::pos_type const &center,
	messages::space_unit const direction,
	messages::space_unit const angle)
{
	switch(etype) {
	case enemy_type::zombie00:
	case enemy_type::zombie01:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::list(messages::mu(0)),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property::type::health,
					 entities::property(messages::mu(3)))
					(entities::property::type::movement_speed,
					 entities::property(messages::mu(20))),
				ai::ai_ptr(
					new ai::simple()),
				weapons::weapon_ptr(
					new weapons::melee(
						env,
						messages::mu(100), // range
						static_cast<time_type>(2), // cd
						messages::mu(4) // damage
					)),
				1,
				static_cast<messages::exp_type>(10)
				));
	case enemy_type::wolf_black:
	case enemy_type::wolf_brown:
	case enemy_type::wolf_white:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::list(messages::mu(0)),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property::type::health,
					 entities::property(messages::mu(1)))
					(entities::property::type::movement_speed,
					 entities::property(messages::mu(80))),
				ai::ai_ptr(
					new ai::simple()),
				weapons::weapon_ptr(
					new weapons::melee(
						env,
						messages::mu(50), // range
						static_cast<time_type>(1), // cd
						messages::mu(1) // damage
					)),
				1,
				static_cast<messages::exp_type>(5)
			 ));
	case enemy_type::skeleton:
		return auto_ptr(
			new enemy(
			 etype,
			 env,
			 damage::list(messages::mu(0)),
			 center,
			 angle,
			 direction,
			 boost::assign::map_list_of
				(entities::property::type::health,
				entities::property(messages::mu(30)))
				(entities::property::type::movement_speed,
				entities::property(messages::mu(40))),
			ai::ai_ptr(
				new ai::simple()),
			weapons::weapon_ptr(
				new weapons::melee(
					env,
					messages::mu(100), // range
					static_cast<time_type>(1), // cd
					messages::mu(7) // damage
				)),
			 1,
			 static_cast<messages::exp_type>(20)
			 ));
	case enemy_type::spider:
		return auto_ptr(
			new enemy(
				etype,
				env,
				damage::list(messages::mu(0)),
				center,
				angle,
				direction,
				boost::assign::map_list_of
					(entities::property::type::health,
					 entities::property(messages::mu(10)))
					(entities::property::type::movement_speed,
					 entities::property(messages::mu(70))),
				ai::ai_ptr(
					new ai::simple()),
				weapons::weapon_ptr(
					new weapons::melee(
						env,
						messages::mu(120), // range
						static_cast<time_type>(2), // cd
						messages::mu(5) // damage
					)),
				1,
				static_cast<messages::exp_type>(15)
				));
	default:
		throw exception(
			SGE_TEXT("Invalid enemy_type in factory!"));
	}
}
