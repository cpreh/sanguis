#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED

#include "entity_with_weapon.hpp"
#include "../environment/object_ptr.hpp"
#include "../perks/tree.hpp"
#include "../perks/list.hpp"
#include "../level_type.hpp"
#include "../string.hpp"
#include "../exp_type.hpp"
#include "../player_id.hpp"
#include "../../perk_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class player : public entity_with_weapon {
public:
	player(
		server::environment::object_ptr,
		damage::armor const &,
		pos_type const &center,
		space_unit direction,
		space_unit angle,
		property_map const &,
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

	server::player_id const
	player_id() const;
private:
	void
	on_die();

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
