#include "melee.hpp"

sanguis::server::projectiles::melee::melee(
	messages::pos_type const& pos,
	const messages::space_unit angle,
	const team::type team_,
	const messages::space_unit damage)
: projectile(
	pos,
	angle,
	1, // some arbitrary value
	team_,
	0,
	0,
	0.1), // short lifetime
  damage(damage)
{}

void sanguis::server::projectiles::melee::do_hit(
	entity &target)
{
	target.damage(damage);
}
