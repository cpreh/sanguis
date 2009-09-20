#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED

#include "../entity.hpp"
#include "../entity_with_weapon_fwd.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../team.hpp"
#include "../../pos_type.hpp"
#include "../../../pickup_type.hpp"
#include "../../../diff_clock.hpp"
#include "../../../messages/auto_ptr.hpp"
#include <sge/time/timer.hpp>
#include <sge/optional_fwd.hpp>
#include <boost/logic/tribool_fwd.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace pickups
{

class pickup : public entity {
public:
	pickup_type::type ptype() const;
protected:
	typedef sge::optional<dim_type> optional_dim;

	pickup(
		pickup_type::type,
		server::environment::load_context_ptr,
		team::type team,
		optional_dim const &dim
	);
private:
	boost::logic::tribool const
	can_collide_with_entity(
		entity const &
	) const;
	
	void
	collision_entity(
		entity &
	);

	void
	update(
		time_type
	);
	
	// TODO: is it ok that pickups are limited to entities with weapons?
	virtual void
	do_pickup(
		entity_with_weapon &receiver
	) = 0;

	messages::auto_ptr add_message() const;

	diff_clock diff_clock_;
	sge::time::timer lifetime;
	pickup_type::type const ptype_;
};

}
}
}
}

#endif
