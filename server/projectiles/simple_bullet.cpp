#include "simple_bullet.hpp"

sanguis::server::projectiles::simple_bullet::simple_bullet(
	messages::pos_type const& pos,
	const messages::space_unit angle,
	const team::type team_,
	const messages::space_unit damage)
: projectile(
	pos,
	angle,
	1,
	team_,
	0.1, // FIXME
	0.1,
	10),
  damage(damage)
{}

void sanguis::server::projectiles::simple_bullet::do_hit(
	entity &target)
{
	target.damage(damage);	
}
