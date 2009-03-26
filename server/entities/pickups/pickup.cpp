#include "pickup.hpp"
#include "../entity_with_weapon.hpp"
#include "../base_parameters.hpp"
#include "../property.hpp"
#include "../../get_dim.hpp"
#include "../../damage_types.hpp"
#include "../../message_converter.hpp"
#include "../../../load/pickup_name.hpp"
#include "../../../load/context.hpp"
#include "../../../messages/add_pickup.hpp"
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <boost/assign/list_of.hpp>

sanguis::pickup_type::type
sanguis::server::entities::pickups::pickup::ptype() const
{
	return ptype_;
}

bool sanguis::server::entities::pickups::pickup::can_collide_with(
	entity const &e) const
{
	return dynamic_cast<entity_with_weapon const * const>(&e) && e.team() == team();
}

void sanguis::server::entities::pickups::pickup::collision(
	entity &e)
{
	do_pickup(dynamic_cast<entity_with_weapon &>(e));
	die();
}

sanguis::server::entities::pickups::pickup::pickup(
	pickup_type::type const ptype_,
	server::environment const &env,
	pos_type const &center,
	team::type const team_,
	optional_dim const &dim_)
:
	entity(
		base_parameters(
			env,
			damage::all(
				messages::mu(1)), // FIXME: create default values for this
			center,
			messages::mu(0), //angle
			messages::mu(0), //direction,
			team_,
			boost::assign::map_list_of
				(entities::property_type::health,
				entities::property(messages::mu(1)))
				(entities::property_type::movement_speed,
				entities::property(messages::mu(0))),
			entity_type::pickup,
			true,
			dim_
			? *dim_
			: default_dim(
				env.load().models(),
				load::pickup_name(
					ptype_)))),
	ptype_(ptype_)
{}

sanguis::messages::auto_ptr
sanguis::server::entities::pickups::pickup::add_message() const
{
	return message_convert(*this);
}
