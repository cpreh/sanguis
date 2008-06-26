#include "pickup.hpp"
#include "../../collision.hpp"
#include "../entity_with_weapon.hpp"
#include <boost/foreach.hpp>

sanguis::server::entities::pickups::pickup::pickup(
	environment const &env,
	messages::pos_type const &pos,
	messages::space_unit const angle,
	messages::space_unit const direction,
	team::type const team_)
: entity(
	env,
	armor_array(), // FIXME
	pos,
	angle,
	direction,
	team_,
	property_map()) // FIXME
{}

void sanguis::server::entities::pickups::pickup::update(
	time_type const time,
	container &entities)
{
	entity::update(
		time,
		entities);

	BOOST_FOREACH(
		entity &e,
		entities)
	{
		if(entity_with_weapon *ew = dynamic_cast<entity_with_weapon *>(&e))
		{
			if(e.team() == team()
			&& collides(
				e,
				*this))
			{
				do_pickup(*ew);
				return;
			}
		}
	}

}

sanguis::messages::dim_type const
sanguis::server::entities::pickups::pickup::dim() const
{
	return messages::dim_type(10,10); // FIXME
}

sanguis::entity_type::type
sanguis::server::entities::pickups::pickup::type() const
{
	return entity_type::pickup;
}

bool sanguis::server::entities::pickups::pickup::invulnerable() const
{
	return true;
}
