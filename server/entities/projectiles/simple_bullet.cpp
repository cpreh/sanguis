#include "simple_bullet.hpp"
#include "../../get_dim.hpp"
#include <boost/assign/list_of.hpp>
#include <cassert>

sanguis::server::entities::projectiles::simple_bullet::simple_bullet(
	environment const &env,
	messages::pos_type const &center,
	messages::space_unit const angle,
	team::type const team_,
	messages::space_unit const damage)
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
			SGE_TEXT("bullet")),
		static_cast<time_type>(10)),
	damage(damage)
{}

sanguis::entity_type::type
sanguis::server::entities::projectiles::simple_bullet::type() const
{
	return entity_type::bullet;
}

void sanguis::server::entities::projectiles::simple_bullet::do_hit(
	hit_vector const &hits)
{
	damage_array const damage_values =
		boost::assign::list_of
		(messages::mu(0))
		(messages::mu(1))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0));
			
	assert(!hits.empty());

	hits[0].get().damage(
		damage,
		damage_values);

	die();
}
