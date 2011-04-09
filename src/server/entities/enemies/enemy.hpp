#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include "../auto_weak_link.hpp"
#include "../body_velocity_combiner.hpp"
#include "../with_ai.hpp"
#include "../with_buffs.hpp"
#include "../with_dim.hpp"
#include "../with_health.hpp"
#include "../with_velocity.hpp"
#include "../movement_speed.hpp"
#include "../../ai/create_function.hpp"
#include "../../environment/load_context_fwd.hpp"
#include "../../weapons/unique_ptr.hpp"
#include "../../probability.hpp"
#include "../../exp.hpp"
#include "../../health.hpp"
#include "../../../enemy_type.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

class enemy
:
	private body_velocity_combiner,
	public with_ai,
	public with_buffs,
	public with_dim,
	public with_health,
	public with_velocity
{
	FCPPT_NONCOPYABLE(
		enemy
	);
public:	
	enemy(
		enemy_type::type,
		server::environment::load_context &,
		damage::armor const &,
		server::health,
		entities::movement_speed,
		ai::create_function const &,
		weapons::unique_ptr weapon,
		server::probability spawn_chance,
		server::exp,
		auto_weak_link spawn_owner = auto_weak_link()
	);

	~enemy();

	enemy_type::type
	etype() const;
private:
	void
	on_update(
		time_type
	);

	messages::auto_ptr
	add_message(
		player_id
	) const;

	entity_type::type
	type() const;

	server::team::type
	team() const;

	void
	on_remove();

	enemy_type::type const etype_;

	server::probability const spawn_chance_;

	server::exp const exp_;

	auto_weak_link const spawn_owner_;
};

}
}
}
}

#endif
