#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED

#include "movable.hpp"
#include "with_auras.hpp"
#include "with_buffs.hpp"
#include "with_dim.hpp"
#include "with_health.hpp"
#include "with_perks.hpp"
#include "with_weapon.hpp"
#include "movement_speed.hpp"
#include "health_type.hpp"
#include "../environment/load_context_ptr.hpp"
#include "../damage/armor.hpp"
#include "../perks/auto_ptr.hpp"
#include "../perks/tree.hpp"
#include "../perks/list.hpp"
#include "../level_type.hpp"
#include "../string.hpp"
#include "../exp_type.hpp"
#include "../player_id.hpp"
#include "../../perk_type.hpp"
#include "../../time_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class player
:
	public movable,
	public with_auras,
	public with_buffs,
	public with_dim,
	public with_health,
	public with_perks,
	public with_weapon
{
public:
	player(
		server::environment::load_context_ptr,
		entities::health_type,
		damage::armor const &,
		entities::movement_speed,
		string const &name,
		server::player_id
	);

	// own functions
	string const name() const;
	exp_type exp() const;
	void exp(exp_type);
	level_type level() const;
	level_type level_delta() const;

	bool
	perk_choosable(
		perk_type::type
	) const;
	
	void
	add_perk(
		perks::auto_ptr
	);
	
	perks::list const
	available_perks() const;

	server::player_id 
	player_id() const;
private:
	void
	on_die();

	void
	add_sight_range(
		entity_id
	);

	void
	remove_sight_range(
		entity_id
	);

	void
	on_update(
		time_type
	);

	messages::auto_ptr
	add_message() const;

	entity_type::type
	type() const;

	server::team::type
	team() const;

	string const name_;
	server::player_id const player_id_;
	exp_type exp_;
	level_type
		level_,
		level_delta_;
	unsigned skill_points_;
	perks::tree perk_tree_;
};

}
}
}

#endif
