#include "melee.hpp"
#include "../property.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::melee::melee(
	server::environment const &env,
	messages::pos_type const& center,
	team::type const team_,
	messages::space_unit const damage)
:
	projectile(
		projectile_type::melee,
		env,
		center,
		messages::mu(0), // angle doesn't matter here
		team_,
		boost::assign::map_list_of
			(
				entities::property_type::health,
				entities::property(messages::mu(1))
			)
			(
				entities::property_type::movement_speed,
				entities::property(messages::mu(0))
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
		(messages::mu(1))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0));
	
	e.damage(
		damage,
		damage_values);
	die();
}
