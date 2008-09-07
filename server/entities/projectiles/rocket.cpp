#include "rocket.hpp"
#include "../../get_dim.hpp"
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::rocket::rocket(
	environment const &env,
	pos_type const &center,
	space_unit const angle,
	team::type const team_,
	space_unit const damage)
:
	projectile(
		env,
		center,
		angle,
		team_,
		boost::assign::map_list_of
			(property::type::health, property(messages::mu(1)))
			(property::type::movement_speed, property(messages::mu(300))),
		default_dim(
			SGE_TEXT("rocket")),
		static_cast<time_type>(10)),
	damage(damage)
{}

void sanguis::server::entities::projectiles::rocket::do_hit(
	entity &)
{
	die();
}

void sanguis::server::entities::projectiles::rocket::do_die()
{
	damage_array const damage_values =
		boost::assign::list_of
		(messages::mu(0))
		(messages::mu(1))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0));
	
	/*insert(
		new aoe_damage(
			env,
			center(),
			team(),
			messages::mu(20),
			damage,
			damage_values));*/
}