#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include "../with_ai.hpp"
#include "../with_buffs.hpp"
#include "../with_dim.hpp"
#include "../with_health.hpp"
#include "../movable.hpp"
#include "../movement_speed.hpp"
#include "../health_type.hpp"
#include "../auto_weak_link.hpp"
#include "../../ai/create_function.hpp"
#include "../../weapons/unique_ptr.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../probability_type.hpp"
#include "../../exp_type.hpp"
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
	public with_ai,
	public with_buffs,
	public with_dim,
	public with_health,
	public movable
{
	FCPPT_NONCOPYABLE(
		enemy
	);
public:	
	enemy(
		enemy_type::type,
		server::environment::load_context_ptr,
		damage::armor const &,
		entities::health_type,
		entities::movement_speed,
		ai::create_function const &,
		weapons::unique_ptr weapon,
		probability_type spawn_chance,
		exp_type exp,
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
	on_die();

	enemy_type::type const etype_;

	probability_type const spawn_chance_;

	exp_type const exp_;

	auto_weak_link const spawn_owner_;
};

}
}
}
}

#endif
