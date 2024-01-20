#ifndef SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_OBJECT_HPP_INCLUDED

#include <sanguis/aura_type_fwd.hpp>
#include <sanguis/buff_type_fwd.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/entity_id.hpp>
#include <sanguis/is_primary_weapon_fwd.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/optional_primary_weapon_type_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/weapon_status_fwd.hpp>
#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/collision/log.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/collision/world/object_unique_ptr.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/top_result_fwd.hpp>
#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/server/angle_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/level.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/player_id_fwd.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/entities/doodad_unique_ptr.hpp>
#include <sanguis/server/entities/insert_parameters_fwd.hpp>
#include <sanguis/server/entities/optional_base_ref_fwd.hpp>
#include <sanguis/server/entities/simple_unique_ptr.hpp>
#include <sanguis/server/entities/with_id_fwd.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/world/context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/info.hpp>
#include <sanguis/server/world/insert_simple_pair_fwd.hpp>
#include <sanguis/server/world/insert_with_id_pair_container.hpp>
#include <sanguis/server/world/insert_with_id_pair_fwd.hpp>
#include <sanguis/server/world/object_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/world/parameters_fwd.hpp>
#include <sanguis/server/world/pickup_spawner.hpp>
#include <sanguis/server/world/sight_range_map.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::world
{

class object : private sanguis::server::environment::object
{
  FCPPT_NONMOVABLE(object);

public:
  object(
      sanguis::server::world::parameters const &,
      sanguis::world_id,
      sanguis::creator::top_result const &,
      sanguis::server::world::difficulty,
      sanguis::world_name &&);

  ~object() override;

  void update(sanguis::duration const &);

  [[nodiscard]] sanguis::server::entities::optional_base_ref insert(
      sanguis::server::entities::simple_unique_ptr &&,
      sanguis::server::entities::insert_parameters const &) override;

  [[nodiscard]] sanguis::server::entities::optional_base_ref insert(
      sanguis::server::entities::with_id_unique_ptr &&,
      sanguis::server::entities::insert_parameters const &) override;

  [[nodiscard]] sanguis::server::entities::optional_base_ref
  insert(sanguis::server::world::insert_with_id_pair &&);

  void insert(sanguis::server::world::insert_with_id_pair_container &&);

  [[nodiscard]] sanguis::server::entities::optional_base_ref
  insert(sanguis::server::world::insert_simple_pair &&);

  [[nodiscard]] sanguis::server::environment::object &environment();

  [[nodiscard]] sanguis::creator::opening_container_array const &openings() const;

  [[nodiscard]] sanguis::world_id world_id() const;

private:
  void player_insertion(sanguis::server::player_id) override;

  template <typename Entity>
  [[nodiscard]] fcppt::optional::reference<Entity> insert_base(
      std::vector<fcppt::unique_ptr<Entity>> &,
      fcppt::unique_ptr<Entity> &&,
      sanguis::server::entities::insert_parameters const &);

public:
  void add_aura(sanguis::entity_id, sanguis::aura_type) override;

  void add_buff(sanguis::entity_id, sanguis::buff_type) override;

  void remove_buff(sanguis::entity_id, sanguis::buff_type) override;

  void weapon_changed(sanguis::entity_id, sanguis::optional_primary_weapon_type) override;

  void got_weapon(sanguis::server::player_id, sanguis::weapon_description const &) override;

  void remove_weapon(sanguis::server::player_id, sanguis::is_primary_weapon) override;

  void magazine_remaining(
      sanguis::server::player_id, sanguis::is_primary_weapon, sanguis::magazine_remaining) override;

  void reload_time(
      sanguis::server::player_id, sanguis::is_primary_weapon, sanguis::duration) override;

  void angle_changed(sanguis::entity_id, sanguis::server::angle) override;

  void center_changed(sanguis::entity_id, sanguis::server::center) override;

  void speed_changed(sanguis::entity_id, sanguis::server::speed) override;

  void weapon_status_changed(sanguis::entity_id, sanguis::weapon_status) override;

  void health_changed(sanguis::entity_id, sanguis::server::health) override;

  void max_health_changed(sanguis::entity_id, sanguis::server::health) override;

  void exp_changed(sanguis::server::player_id, sanguis::server::exp) override;

  void level_changed(sanguis::server::player_id, sanguis::server::level) override;

  void pickup_chance(
      sanguis::server::pickup_probability,
      sanguis::server::entities::enemies::difficulty,
      sanguis::server::center) override;

  void request_transfer(sanguis::entity_id) override;

  void add_portal_blocker() override;

  void remove_portal_blocker() override;

  [[nodiscard]] sanguis::server::world::difficulty difficulty() const override;

  [[nodiscard]] sanguis::collision::log const &collision_log() const override;

  [[nodiscard]] sanguis::collision::world::object &collision_world() const override;

  [[nodiscard]] sanguis::creator::grid const &grid() const override;

  [[nodiscard]] sanguis::server::environment::load_context &load_context() const override;

  void add_sight_range(
      sanguis::server::player_id,
      sanguis::server::entities::with_id const &,
      sanguis::collision::world::created) override;

  void remove_sight_range(
      sanguis::server::player_id, sanguis::server::entities::with_id const &) override;

  void remove_player(sanguis::server::player_id) override;

private:
  // own functions
  void send_entity_specific(sanguis::entity_id, sanguis::messages::server::base const &);

  void send_player_specific(sanguis::server::player_id, sanguis::messages::server::base const &);

  void insert_spawns(
      sanguis::creator::spawn_container const &,
      sanguis::random_generator_ref,
      sanguis::server::weapons::common_parameters const &);

  void insert_destructibles(
      sanguis::creator::destructible_container const &,
      sanguis::random_generator & // NOLINT(google-runtime-references)
  ); // NOLINT(google-runtime-references)

  fcppt::log::object log_;

  sanguis::server::world::info const info_;

  sanguis::server::world::difficulty const difficulty_;

  sanguis::creator::grid const grid_;

  sanguis::server::world::context &global_context_;

  sanguis::server::environment::load_context &load_context_;

  sanguis::collision::log const collision_log_;

  sanguis::collision::world::object_unique_ptr const collision_world_;

  sanguis::server::world::sight_range_map sight_ranges_;

  using entity_map = std::map<sanguis::entity_id, sanguis::server::entities::with_id_unique_ptr>;

  entity_map entities_;

  using base_container = std::vector<sanguis::server::entities::simple_unique_ptr>;

  base_container server_entities_;

  using doodad_container = std::vector<sanguis::server::entities::doodad_unique_ptr>;

  doodad_container portal_blockers_;

  unsigned portal_block_count_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)

  sanguis::server::world::pickup_spawner pickup_spawner_;
};

}

#endif
