#ifndef SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED

#include "entity_with_ai.hpp"
#include "../../friend_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class friend_
:
	public with_ai,
	public with_armor,
	public with_buffs
{
public:
	friend_(
		friend_type::type,
		server::environment::load_context_ptr,
		damage::armor const &,
		property_map const &,
		ai::auto_ptr,
		weapons::auto_ptr weapon
	);
private:
	entity_type::type
	type() const;

	bool
	invulnerable() const;

	server::team::type
	team() const;
	
	messages::auto_ptr
	add_message() const;

	boost::logic::tribool const
	can_collide_with_entity(
		entity const &
	) const;

	friend_type::type const ftype_;
};

}
}
}

#endif
