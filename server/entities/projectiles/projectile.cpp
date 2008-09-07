#include "projectile.hpp"
#include "../base_parameters.hpp"
#include "../../collision.hpp"
#include <sge/time/second.hpp>
#include <boost/foreach.hpp>

sanguis::server::entities::projectiles::projectile::projectile(
	environment const &env,
	armor_array const &armor,
	messages::pos_type const& pos,
	messages::space_unit const angle,
	team::type const team_,
	property_map const &properties,
	time_type const lifetime)
:
	entity(
		base_parameters(
			env,
			armor,
			pos,
			angle,
			angle,
			team_,
			properties,
			entity_type::bullet,
			true,
			dim_type(1,1))), // FIXME
  lifetime(
  	sge::time::second(
		lifetime))
{}

void sanguis::server::entities::projectiles::projectile::die()
{
	entity::die();
	do_die();
}

void sanguis::server::entities::projectiles::projectile::update(
	const time_type time,
	container &entities)
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
		&& !e.dead()
		&& collides(
			e,
			*this))
			do_hit(e);
		if(dead())
			return;
	}
}

sanguis::messages::space_unit
sanguis::server::entities::projectiles::projectile::max_speed() const
{
	return max_speed_;	
}

void sanguis::server::entities::projectiles::projectile::do_die()
{}
