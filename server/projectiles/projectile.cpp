#include "projectile.hpp"

sanguis::server::projectiles::projectile::projectile(
	messages::pos_type const& pos,
	const messages::space_unit angle,
	const messages::space_unit max_health,
	const team::type team_,
	const messages::space_unit speed,
	const time_type lifetime)
: entity(
	pos,
	angle,
	angle,
	max_health,
	max_health,
	team_,
	speed),
  lifetime(lifetime)
{}

bool sanguis::server::projectiles::projectile::invulnerable() const
{
	return true; // most bullets will be invulnerable
}

void sanguis::server::projectiles::projectile::update(
	const time_type time)
{
	if(lifetime.expired())
		die();
	// TODO: check for colissions with other teams here
}

void sanguis::server::projectiles::projectile::die()
{}
