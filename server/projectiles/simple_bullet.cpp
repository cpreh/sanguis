#include "simple_bullet.hpp"
#include "../get_dim.hpp"
#include <boost/assign/list_of.hpp>

namespace
{

const sanguis::messages::space_unit bullet_speed(
	sanguis::messages::mu(200));

}

sanguis::server::projectiles::simple_bullet::simple_bullet(
	environment const & env,
	armor_array const &armor,
	messages::pos_type const& pos,
	messages::space_unit const  angle,
	team::type const  team_,
	messages::space_unit const  damage)
: projectile(
		env,
		armor,
		pos,
		angle,
		team_,
		boost::assign::map_list_of
			(entity::property::type::health, entity::property(messages::mu(1)))
			(entity::property::type::movement_speed, entity::property(messages::mu(1))),
		static_cast<time_type>(10)),
  damage(damage)
{}

sanguis::entity_type::type
sanguis::server::projectiles::simple_bullet::type() const
{
	return entity_type::bullet;
}

sanguis::messages::dim_type
sanguis::server::projectiles::simple_bullet::dim() const
{
	return get_dim(SGE_TEXT("bullet"), SGE_TEXT("default"));
}

void sanguis::server::projectiles::simple_bullet::do_hit(
	entity &target)
{
	const damage_array damage_values =
		boost::assign::list_of
		(messages::mu(0))
		(messages::mu(1))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0));
			
	target.damage(
		damage,
		damage_values);

	die();
}
