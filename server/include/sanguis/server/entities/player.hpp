#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED

#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/collision/world/group_field_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/skill_points.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/string.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/armor_array_fwd.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_auras_id.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/pickups/weapon_ref.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/perks/tree/object_unique_ptr.hpp>
#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_wrapper_comparison.hpp>
#include <fcppt/reference_wrapper_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class player
:
	public virtual sanguis::server::entities::ifaces::with_team,
	public sanguis::server::entities::with_velocity,
	public sanguis::server::entities::with_auras_id,
	public sanguis::server::entities::with_buffs,
	public sanguis::server::entities::with_id,
	public sanguis::server::entities::with_health,
	public sanguis::server::entities::with_links,
	public sanguis::server::entities::with_perks,
	public sanguis::server::entities::with_weapon
{
	FCPPT_NONCOPYABLE(
		player
	);
public:
	player(
		sanguis::random_generator &,
		sanguis::server::environment::load_context &,
		sanguis::server::health,
		sanguis::server::damage::armor_array const &,
		sanguis::server::entities::movement_speed,
		sanguis::server::string const &name,
		sanguis::server::player_id
	);

	~player();

	// own functions
	sanguis::server::string const &
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
		sanguis::perk_type
	);

	void
	change_speed(
		sanguis::server::speed
	);

	void
	drop_or_pickup_weapon(
		sanguis::is_primary_weapon
	);

	sanguis::server::perks::tree::object const &
	perk_tree() const;

	sanguis::server::skill_points const
	skill_points() const;

	sanguis::server::player_id const
	player_id() const;

	sanguis::server::level const
	level() const;

	sanguis::server::team
	team() const
	override;
private:
	void
	remove()
	override;

	void
	update_speed();

	void
	add_sight_range(
		sanguis::entity_id
	);

	void
	remove_sight_range(
		sanguis::entity_id
	);

	void
	weapon_pickup_add_candidate(
		sanguis::server::entities::pickups::weapon &
	);

	void
	weapon_pickup_remove_candidate(
		sanguis::server::entities::pickups::weapon &
	);

	void
	update()
	override;

	sanguis::messages::server::unique_ptr
	add_message(
		sanguis::server::player_id
	) const
	override;

	template<
		typename Message
	>
	sanguis::messages::server::unique_ptr
	add_message_impl() const;

	void
	on_new_weapon(
		sanguis::server::weapons::weapon const &
	)
	override;

	void
	on_drop_weapon(
		sanguis::is_primary_weapon
	)
	override;

	void
	on_magazine_remaining(
		sanguis::is_primary_weapon,
		sanguis::magazine_remaining
	)
	override;

	sanguis::collision::world::group_field const
	collision_groups() const
	override;

	typedef
	std::set<
		sanguis::server::entities::pickups::weapon_ref
	>
	weapon_pickup_set;

	sanguis::server::string const name_;

	sanguis::server::player_id const player_id_;

	sanguis::server::exp exp_;

	sanguis::server::level level_;

	sanguis::server::skill_points skill_points_;

	sanguis::server::perks::tree::object_unique_ptr const perk_tree_;

	sanguis::server::speed desired_speed_;

	weapon_pickup_set weapon_pickups_;
};

}
}
}

#endif
