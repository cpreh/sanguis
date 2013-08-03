#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/perks/unique_ptr.hpp>
#include <sanguis/server/perks/tree/object_fwd.hpp>
#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class player
:
	public virtual sanguis::server::entities::ifaces::with_team,
	private sanguis::server::entities::body_velocity_combiner,
	public sanguis::server::entities::with_auras,
	public sanguis::server::entities::with_body,
	public sanguis::server::entities::with_buffs,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_health,
	public sanguis::server::entities::with_links,
	public sanguis::server::entities::with_perks,
	public sanguis::server::entities::with_velocity,
	public sanguis::server::entities::with_weapon
{
	FCPPT_NONCOPYABLE(
		player
	);
public:
	player(
		sanguis::diff_clock const &,
		sanguis::server::environment::load_context &,
		sanguis::server::health,
		sanguis::server::damage::armor const &,
		sanguis::server::entities::movement_speed,
		sanguis::server::string const &name,
		sanguis::server::player_id
	);

	~player();

	// own functions
	sanguis::server::string const
	name() const;

	void
	add_exp(
		sanguis::server::exp
	);

	bool
	perk_choosable(
		sanguis::perk_type
	) const;

	void
	add_perk(
		sanguis::server::perks::unique_ptr &&
	);

	void
	center_from_client(
		sanguis::server::center const &
	);

	sanguis::server::perks::tree::object const &
	perk_tree() const;

	sanguis::server::player_id const
	player_id() const;

	sanguis::server::team
	team() const
	override;
private:
	void
	on_remove()
	override;

	void
	add_sight_range(
		sanguis::entity_id
	);

	void
	remove_sight_range(
		sanguis::entity_id
	);

	void
	on_update()
	override;

	sanguis::messages::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	void
	on_new_weapon(
		sanguis::server::weapons::weapon const &
	)
	override;

	sanguis::server::collision::group_vector
	collision_groups() const
	override;

	template<
		typename Message
	>
	sanguis::messages::unique_ptr
	make_add_message() const;

	sanguis::server::string const name_;

	sanguis::server::player_id const player_id_;

	sanguis::server::exp exp_;

	sanguis::server::level level_;

	unsigned skill_points_;

	typedef fcppt::scoped_ptr<
		sanguis::server::perks::tree::object
	> perk_tree_scoped_ptr;

	perk_tree_scoped_ptr perk_tree_;
};

}
}
}

#endif
