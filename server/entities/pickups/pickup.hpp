#ifndef SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PICKUPS_PICKUP_HPP_INCLUDED

#include "../entity.hpp"
#include "../entity_with_weapon_fwd.hpp"
#include "../../../pickup_type.hpp"
#include <boost/optional.hpp>

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
	typedef boost::optional<dim_type> optional_dim;

	pickup(
		pickup_type::type,
		server::environment const &,
		pos_type const &center,
		team::type team,
		optional_dim const &dim
			= optional_dim());
private:
	bool
	can_collide_with_entity(
		entity const &) const;
	
	void
	collision_entity(
		entity &);

	// TODO: is it ok that pickups are limited to entities with weapons?
	virtual void do_pickup(
		entity_with_weapon &receiver) = 0;

	messages::auto_ptr add_message() const;

	pickup_type::type ptype_;
};

}
}
}
}

#endif
