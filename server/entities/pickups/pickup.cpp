#include "pickup.hpp"
#include "../entity_with_weapon.hpp"
#include "../base_parameters.hpp"
#include "../property.hpp"
#include "../../get_dim.hpp"
#include "../../damage_types.hpp"
#include "../../../load/pickup_name.hpp"
#include "../../../load/context.hpp"
#include "../../../messages/add_pickup.hpp"
#include "../../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/text.hpp>
#include <boost/assign/list_of.hpp>

sanguis::pickup_type::type
sanguis::server::entities::pickups::pickup::ptype() const
{
	return ptype_;
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
				static_cast<space_unit>(1)), // FIXME: create default values for this
			center,
			static_cast<space_unit>(0), //angle
			static_cast<space_unit>(0), //direction,
			team_,
			boost::assign::map_list_of
				(entities::property_type::health,
				entities::property(static_cast<space_unit>(1)))
				(entities::property_type::movement_speed,
				entities::property(static_cast<space_unit>(0))),
			entity_type::pickup,
			true,
			dim_
			? *dim_
			: default_dim(
				env.load().models(),
				load::pickup_name(
					ptype_
				)
			)
		)
	),
	ptype_(ptype_)
{}

bool
sanguis::server::entities::pickups::pickup::can_collide_with_entity(
	entity const &e) const
{
	return dynamic_cast<entity_with_weapon const * const>(&e) && e.team() == team();
}

void
sanguis::server::entities::pickups::pickup::collision_entity(
	entity &e)
{
	do_pickup(dynamic_cast<entity_with_weapon &>(e));
	die();
}

sanguis::messages::auto_ptr
sanguis::server::entities::pickups::pickup::add_message() const
{
	return messages::create(
		messages::add_pickup(
			id(),
			pos(),
			angle(),
			abs_speed(),
			health(),
			max_health(),
			dim(),
			ptype()
		)
	);
}
