#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/perk_type_fwd.hpp>
#include <sanguis/player_name.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/skill_points.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/damage/armor_array_fwd.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_auras_id.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/pickups/weapon_fwd.hpp>
#include <sanguis/server/entities/pickups/weapon_ref.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/perks/tree/container.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/weapon_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/reference_std_hash.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::entities
{

class player : public virtual sanguis::server::entities::ifaces::with_team,
               public sanguis::server::entities::with_velocity,
               public sanguis::server::entities::with_auras_id,
               public sanguis::server::entities::with_buffs,
               public sanguis::server::entities::with_id,
               public sanguis::server::entities::with_health,
               public sanguis::server::entities::with_links,
               public sanguis::server::entities::with_perks,
               public sanguis::server::entities::with_weapon
{
  FCPPT_NONMOVABLE(player);

public:
  player(
      sanguis::random_generator_ref,
      sanguis::server::weapons::common_parameters const &,
      sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
      sanguis::server::health,
      sanguis::server::damage::armor_array const &,
      sanguis::server::entities::movement_speed,
      sanguis::player_name &&,
      sanguis::server::player_id);

  ~player() override;

  // own functions
  [[nodiscard]] sanguis::player_name const &name() const;

  void add_exp(sanguis::server::exp);

  [[nodiscard]] bool perk_choosable(sanguis::perk_type) const;

  void add_perk(sanguis::perk_type);

  void change_speed(sanguis::server::speed const &);

  void drop_or_pickup_weapon(sanguis::is_primary_weapon);

  [[nodiscard]] sanguis::server::perks::tree::container const &perk_tree() const;

  [[nodiscard]] sanguis::server::skill_points skill_points() const;

  [[nodiscard]] sanguis::server::player_id player_id() const;

  [[nodiscard]] sanguis::server::level level() const;

  [[nodiscard]] sanguis::server::team team() const override;

private:
  void transfer_to_world() override;

  void remove_from_game() override;

  void update_speed();

  void
  add_sight_range(sanguis::server::entities::with_id const &, sanguis::collision::world::created);

  void remove_sight_range(sanguis::server::entities::with_id const &);

  void weapon_pickup_add_candidate(sanguis::server::entities::pickups::weapon_ref);

  void weapon_pickup_remove_candidate(
      sanguis::server::entities::pickups::weapon & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  void update() override;

  [[nodiscard]] sanguis::messages::server::unique_ptr
      add_message(sanguis::server::player_id, sanguis::collision::world::created) const override;

  template <typename Message>
  [[nodiscard]] sanguis::messages::server::unique_ptr
      add_message_impl(sanguis::collision::world::created) const;

  void on_new_weapon(sanguis::server::weapons::weapon const &) override;

  void on_drop_weapon(sanguis::is_primary_weapon) override;

  void on_magazine_remaining(sanguis::is_primary_weapon, sanguis::magazine_remaining) override;

  void on_reload_time(sanguis::is_primary_weapon, sanguis::duration) override;

  [[nodiscard]] sanguis::collision::world::body_group collision_group() const override;

  using weapon_pickup_set = std::set<sanguis::server::entities::pickups::weapon_ref>;

  sanguis::player_name const name_;

  sanguis::server::player_id const player_id_;

  sanguis::server::exp exp_;

  sanguis::server::level level_;

  sanguis::server::skill_points skill_points_;

  sanguis::server::perks::tree::container perk_tree_;

  sanguis::server::speed desired_speed_;

  weapon_pickup_set weapon_pickups_;
};

}

#endif
