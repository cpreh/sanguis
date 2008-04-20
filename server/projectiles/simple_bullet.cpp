#include "simple_bullet.hpp"

namespace
{

const sanguis::messages::space_unit bullet_speed(
	sanguis::messages::mu(0.1));

}

sanguis::server::projectiles::simple_bullet::simple_bullet(
	messages::pos_type const& pos,
	const messages::space_unit angle,
	const team::type team_,
	const messages::space_unit damage)
: projectile(
	pos,
	angle,
	messages::mu(1),
	team_,
	bullet_speed,
	bullet_speed,
	static_cast<time_type>(10)),
  damage(damage)
{}

sanguis::entity_type::type
sanguis::server::projectiles::simple_bullet::type() const
{
	return entity_type::bullet;
}

void sanguis::server::projectiles::simple_bullet::do_hit(
	entity &target)
{
	target.damage(damage);	
}
