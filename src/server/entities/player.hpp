#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED

#include "body_velocity_combiner.hpp"
#include "with_auras.hpp"
#include "with_body.hpp"
#include "with_buffs.hpp"
#include "with_health.hpp"
#include "with_perks.hpp"
#include "with_velocity.hpp"
#include "with_weapon.hpp"
#include "movement_speed.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../damage/armor.hpp"
#include "../perks/unique_ptr.hpp"
#include "../perks/tree/object.hpp"
#include "../exp.hpp"
#include "../health.hpp"
#include "../level.hpp"
#include "../player_id.hpp"
#include "../string.hpp"
#include "../../diff_clock_fwd.hpp"
#include "../../perk_type.hpp"
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class player
:
	private body_velocity_combiner,
	public with_auras,
	public with_body,
	public with_buffs,
	public with_health,
	public with_perks,
	public with_velocity,
	public with_weapon
{
	FCPPT_NONCOPYABLE(
		player
	);
public:
	player(
		sanguis::diff_clock const &,
		server::environment::load_context &,
		server::health,
		damage::armor const &,
		entities::movement_speed,
		server::string const &name,
		server::player_id
	);

	~player();

	// own functions
	server::string const
	name() const;

	void
	add_exp(
		server::exp
	);

	bool
	perk_choosable(
		perk_type::type
	) const;

	void
	add_perk(
		perks::unique_ptr
	);

	perks::tree::object const &
	perk_tree() const;

	server::player_id
	player_id() const;
private:
	void
	on_remove();

	void
	add_sight_range(
		sanguis::entity_id
	);

	void
	remove_sight_range(
		sanguis::entity_id
	);

	void
	on_update();

	messages::auto_ptr
	add_message(
		server::player_id
	) const;

	sanguis::entity_type::type
	type() const;

	server::team::type
	team() const;

	void
	on_new_weapon(
		weapon_type::type
	);

	template<
		typename Message
	>
	messages::auto_ptr
	make_add_message() const;

	server::string const name_;

	server::player_id const player_id_;

	server::exp exp_;

	server::level level_;

	unsigned skill_points_;

	typedef fcppt::scoped_ptr<
		perks::tree::object
	> perk_tree_scoped_ptr;

	perk_tree_scoped_ptr perk_tree_;
};

}
}
}

#endif
