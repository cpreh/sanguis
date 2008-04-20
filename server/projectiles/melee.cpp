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

sanguis::entity_type::type
sanguis::server::projectiles::melee::type() const
{
	return entity_type::indeterminate;
}

sanguis::messages::dim_type
sanguis::server::projectiles::melee::dim() const
{
	return messages::dim_type(1,1); // TODO: maybe allow cleaving attacks?
}

void sanguis::server::projectiles::melee::do_hit(
	entity &target)
{
	target.damage(damage);
}
