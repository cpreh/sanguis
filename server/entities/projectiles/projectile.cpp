#include "projectile.hpp"
#include "../base_parameters.hpp"
#include "../../collision.hpp"
#include "../../damage_types.hpp"
#include <sge/time/second.hpp>
#include <boost/foreach.hpp>

sanguis::server::entities::projectiles::projectile::projectile(
	environment const &env,
	pos_type const& center,
	space_unit const angle,
	team::type const team_,
	property_map const &properties,
	dim_type const &dim,
	time_type const lifetime)
:
	entity(
		base_parameters(
			env,
			damage::list(
				messages::mu(0)),
			center,
			angle,
			angle,
			team_,
			properties,
			entity_type::bullet,
			true,
			dim)),
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
	time_type const time,
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

	hit_vector hits;

	BOOST_FOREACH(
		entity &e,
		entities)
	{
		if(e.team() != team()
		&& !e.dead()
		&& collides(
			e,
			*this))
			hits.push_back(e);
	}

	if(!hits.empty())
		do_hit(hits);
}

sanguis::messages::space_unit
sanguis::server::entities::projectiles::projectile::max_speed() const
{
	return max_speed_;	
}

void sanguis::server::entities::projectiles::projectile::do_die()
{}
