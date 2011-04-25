#ifndef SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED

#include "body_velocity_combiner.hpp"
#include "with_ai.hpp"
#include "with_body.hpp"
#include "with_buffs.hpp"
#include "with_health.hpp"
#include "with_velocity.hpp"
#include "movement_speed.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../damage/armor.hpp"
#include "../ai/create_function.hpp"
#include "../weapons/unique_ptr.hpp"
#include "../health.hpp"
#include "../../friend_type.hpp"
#include "../../time_delta_fwd.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class friend_
:
	private body_velocity_combiner,
	public with_ai,
	public with_body,
	public with_buffs,
	public with_health,
	public with_velocity
{
	FCPPT_NONCOPYABLE(
		friend_
	);
public:
	friend_(
		friend_type::type,
		server::environment::load_context &,
		damage::armor const &,
		server::health,
		entities::movement_speed,
		ai::create_function const &,
		weapons::unique_ptr weapon
	);
private:
	void
	on_update(
		sanguis::time_delta const &
	);

	entity_type::type
	type() const;

	server::team::type
	team() const;
	
	messages::auto_ptr
	add_message(
		server::player_id
	) const;

	friend_type::type const ftype_;
};

}
}
}

#endif
