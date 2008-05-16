#include "aura.hpp"
#include "../../collision.hpp"
#include <boost/foreach.hpp>

sanguis::server::entities::auras::aura::aura(
	environment const &env,
	messages::pos_type const &pos,
	const messages::space_unit radius_,
	const team::type team)
: entity(
	env,
	armor_array(),
	pos,
	messages::mu(0), // angle
	messages::mu(0), // direction
	team,
	property_map())
{}

void sanguis::server::entities::auras::aura::update(
	time_type,
	container &entities)
{
	BOOST_FOREACH(entity &e, entities)
		if(collides(e, *this))
			do_effect(e);
}

bool sanguis::server::entities::auras::aura::invulnerable() const
{
	return true;
}

sanguis::messages::space_unit
sanguis::server::entities::auras::aura::max_speed() const
{
	return messages::mu(0);
}
