#ifndef SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED

#include "with_ai.hpp"
#include "with_buffs.hpp"
#include "with_dim.hpp"
#include "with_health.hpp"
#include "movable.hpp"
#include "movement_speed.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../damage/armor.hpp"
#include "../ai/create_function.hpp"
#include "../weapons/auto_ptr.hpp"
#include "../health_type.hpp"
#include "../../friend_type.hpp"
#include "../../time_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class friend_
:
	public with_ai,
	public with_buffs,
	public with_dim,
	public with_health,
	public movable
{
public:
	friend_(
		friend_type::type,
		server::environment::load_context_ptr,
		damage::armor const &,
		health_type health,
		entities::movement_speed,
		ai::create_function const &,
		weapons::auto_ptr weapon
	);
private:
	void
	on_update(
		time_type
	);

	entity_type::type
	type() const;

	server::team::type
	team() const;
	
	messages::auto_ptr
	add_message(
		server::player_id
	) const;

	boost::logic::tribool const
	can_collide_with_entity(
		base const &
	) const;

	friend_type::type const ftype_;
};

}
}
}

#endif
