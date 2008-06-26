#include "pickup.hpp"
#include "../../collision.hpp"
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
		if(e.team() == team()
		&& collides(
			e,
			*this))
		{
			do_pickup(e);
			return;
		}
	}

}
