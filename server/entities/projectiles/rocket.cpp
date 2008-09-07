#include "rocket.hpp"
#include "aoe_damage.hpp"
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
		projectile_type::rocket,
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
	
	insert(
		auto_ptr(
			new aoe_damage(
				get_environment(),
				center(),
				team(),
				messages::mu(20),
				damage,
				1,
				static_cast<time_type>(0),
				damage_values)));
}
