#include "pickup.hpp"
#include "../entity_with_weapon.hpp"
#include "../base_parameters.hpp"
#include "../../get_dim.hpp"
#include "../../damage_types.hpp"
#include "../../collision.hpp"
#include "../../message_converter.hpp"
#include "../../../load/pickup_name.hpp"
#include "../../../messages/add_pickup.hpp"
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <boost/assign/list_of.hpp>

sanguis::pickup_type::type
sanguis::server::entities::pickups::pickup::ptype() const
{
	return ptype_;
}

sanguis::server::entities::pickups::pickup::pickup(
	pickup_type::type const ptype_,
	environment const &env,
	messages::pos_type const &pos,
	team::type const team_)
:
	entity(
		base_parameters(
			env,
			damage::all(
				messages::mu(1)), // FIXME: create default values for this
			pos,
			messages::mu(0), //angle
			messages::mu(0), //direction,
			team_,
			boost::assign::map_list_of
				(entities::property::type::health,
				entities::property(messages::mu(1)))
				(entities::property::type::movement_speed,
				entities::property(messages::mu(0))),
			entity_type::bullet,
			true,
			load::pickup_name(
				ptype_)
				? default_dim(
					*load::pickup_name(
						ptype_))
				: dim_type(0, 0))),
	ptype_(ptype_)
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
				die();
				return;
			}
		}
	}
}

sanguis::messages::auto_ptr
sanguis::server::entities::pickups::pickup::add_message() const
{
	return message_convert<messages::add_pickup>(*this);
}
