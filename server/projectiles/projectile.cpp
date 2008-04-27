#include "projectile.hpp"
#include "../collision.hpp"
#include "../../time_util.hpp"
#include <sge/time.hpp>
#include <boost/foreach.hpp>

sanguis::server::projectiles::projectile::projectile(
	environment const &env,
	armor_array const &armor,
	messages::pos_type const& pos,
	messages::space_unit const angle,
	messages::space_unit const max_health,
	team::type const team_,
	messages::space_unit const speed,
	messages::space_unit const max_speed_,
	time_type const lifetime)
: entity(
	env,
	armor,
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

void sanguis::server::projectiles::projectile::die()
{
	entity::die();
	do_die();
}

bool sanguis::server::projectiles::projectile::invulnerable() const
{
	return true; // most bullets will be invulnerable
}

void sanguis::server::projectiles::projectile::update(
	const time_type time,
	entity_container &entities)
{
	entity::update(
		time,
		entities);

	if(lifetime.expired())
	{
		die();
		return;
	}

	BOOST_FOREACH(
		entity &e,
		entities)
	{
		if(e.team() != team()
		&& collides(
			e,
			*this))
			do_hit(e);
		if(dead())
			return;
	}
}

sanguis::messages::space_unit
sanguis::server::projectiles::projectile::max_speed() const
{
	return max_speed_;	
}

void sanguis::server::projectiles::projectile::do_die()
{}
