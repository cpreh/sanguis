#include "melee.hpp"
#include "../property.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::melee::melee(
	server::environment const &env,
	pos_type const& center,
	team::type const team_,
	space_unit const damage)
:
	projectile(
		projectile_type::melee,
		env,
		center,
		static_cast<space_unit>(0), // angle doesn't matter here
		team_,
		boost::assign::map_list_of
			(
				entities::property_type::health,
				entities::property(static_cast<space_unit>(1))
			)
			(
				entities::property_type::movement_speed,
				entities::property(static_cast<space_unit>(0))
			),
		dim_type(1, 1),
		static_cast<time_type>(1)), // short lifetime
	damage(damage)
{}

void sanguis::server::entities::projectiles::melee::collision(
	entity &e)
{
	damage_array const damage_values =
		boost::assign::list_of
		(static_cast<space_unit>(1))
		(static_cast<space_unit>(0))
		(static_cast<space_unit>(0))
		(static_cast<space_unit>(0))
		(static_cast<space_unit>(0));
	
	e.damage(
		damage,
		damage_values);
	die();
}
