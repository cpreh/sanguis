#include "simple_bullet.hpp"
#include "../property.hpp"
#include "../../get_dim.hpp"
#include "../../../load/context.hpp"
#include <sge/text.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	server::environment const &env,
	messages::pos_type const &center,
	messages::space_unit const angle,
	team::type const team_,
	messages::space_unit const damage)
:
	projectile(
		projectile_type::simple_bullet,
		env,
		center,
		angle,
		team_,
		boost::assign::map_list_of
			(
				entities::property_type::health,
				entities::property(messages::mu(1))
			)
			(
				entities::property_type::movement_speed,
				entities::property(messages::mu(500))
			),
		default_dim(
			env.load().models(),
			SGE_TEXT("bullet")),
		static_cast<time_type>(10)),
	damage(damage)
{}

void sanguis::server::entities::projectiles::simple_bullet::collision(
	entity &e)
{
	damage_array const damage_values =
		boost::assign::list_of
		(messages::mu(0))
		(messages::mu(1))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0));
			
	e.damage(
		damage,
		damage_values);

	die();
}
