#include "projectile.hpp"
#include "../../time_util.hpp"
#include <sge/time.hpp>

sanguis::server::projectiles::projectile::projectile(
	messages::pos_type const& pos,
	const messages::space_unit angle,
	const messages::space_unit max_health,
	const team::type team_,
	const messages::space_unit speed,
	const messages::space_unit max_speed_,
	const time_type lifetime)
: entity(
	pos,
	angle,
	angle,
	max_health,
	max_health,
	team_,
	speed),
  max_speed_(max_speed_),
  lifetime(
  	to_sge_time(
		lifetime))
{}

bool sanguis::server::projectiles::projectile::invulnerable() const
{
	return true; // most bullets will be invulnerable
}

void sanguis::server::projectiles::projectile::update(
	const time_type time)
{
	entity::update(time);

//	if(lifetime.expired())
//		die();
	// TODO: check for collisions with other teams here
}

sanguis::messages::space_unit
sanguis::server::projectiles::projectile::max_speed() const
{
	return max_speed_;	
}

sanguis::messages::dim_type
sanguis::server::projectiles::projectile::dim() const
{
	return messages::dim_type(5,5); // FIXME
}

void sanguis::server::projectiles::projectile::die()
{
	entity::die();
	do_die();
}

void sanguis::server::projectiles::projectile::do_die()
{}
