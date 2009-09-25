#include "pickup.hpp"
#include "../with_weapon.hpp"
#include "../base_parameters.hpp"
#include "../../environment/load_context.hpp"
#include "../../../load/pickup_name.hpp"
#include "../../../messages/add_pickup.hpp"
#include "../../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/time/second.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/optional_impl.hpp>
#include <sge/text.hpp>
#include <boost/logic/tribool.hpp>

sanguis::pickup_type::type
sanguis::server::entities::pickups::pickup::ptype() const
{
	return ptype_;
}

sanguis::server::entities::pickups::pickup::pickup(
	pickup_type::type const ptype_,
	server::environment::load_context_ptr const load_context,
	team::type const team_,
	optional_dim const &dim_
)
:
	base(),
	with_dim(
		dim_
		?
			*dim_
		:
			load_context->entity_dim(
				load::pickup_name(
					ptype_
				)
			)
	),
	team_(team_),
	ptype_(ptype_),
	diff_clock_(),
	lifetime(
		sge::time::second(
			30
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
{}

bool
sanguis::server::entities::pickups::pickup::dead() const
{
	return life_time.expired();
}

bool
sanguis::server::entities::pickups::pickup::invulnerable() const
{
	return true;
}

sanguis::entity_type::type
sanguis::server::entities::pickups::pickup::type() const
{
	return entity_type::pickup;
}

sanguis::server::team::type
sanguis::server::entities::pickups::pickup::team() const
{
	return team_;
}

boost::logic::tribool const
sanguis::server::entities::pickups::pickup::can_collide_with_entity(
	base const &e
) const
{
	return
		e.team() == team()
		&& dynamic_cast<
			with_weapon const *
		>(&e);
}

void
sanguis::server::entities::pickups::pickup::collision_entity_begin(
	base &e
)
{
	// if something is spawned by this pickup that can pickup entities itself
	// we will get an endless loop
	if(dead())
		return;
	
	do_pickup(
		dynamic_cast<
			with_weapon &
		>(
			e
		)
	);

	life_time.expire();
}

void
sanguis::server::entities::pickups::pickup::update(
	time_type const time
)
{
	entity::update(
		time
	);

	diff_clock_.update(
		time
	);
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
			health_type(0), // TODO!
			health_type(0),
			dim(),
			ptype()
		)
	);
}
