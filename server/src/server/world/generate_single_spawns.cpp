#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/load/model/enemy_path.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_id.hpp> // NOLINT(misc-include-cleaner)
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/generate_single_spawns.hpp>
#include <sanguis/server/world/insert_with_id_pair_container.hpp>
#include <sanguis/server/world/place_multiple.hpp>
#include <sanguis/server/world/place_with_id_callback.hpp>

sanguis::server::world::insert_with_id_pair_container
sanguis::server::world::generate_single_spawns(
    sanguis::creator::enemy_type const _enemy_type,
    sanguis::creator::enemy_kind const _enemy_kind,
    sanguis::creator::spawn_pos const &_pos,
    sanguis::server::weapons::common_parameters const &_weapons_parameters,
    sanguis::random_generator_ref const _random_generator,
    sanguis::server::environment::load_context &_load_context,
    sanguis::server::world::difficulty const _difficulty)
{
  return sanguis::server::world::place_multiple(
      _random_generator.get(),
      sanguis::server::world::place_with_id_callback(
          [&_random_generator,
           &_weapons_parameters,
           _enemy_type,
           _enemy_kind,
           _difficulty,
           &_load_context]
          {
            return sanguis::server::entities::enemies::create(
                _random_generator,
                _weapons_parameters,
                _enemy_type,
                _enemy_kind,
                _difficulty,
                _load_context,
                sanguis::server::entities::spawn_owner(sanguis::server::entities::auto_weak_link()),
                sanguis::server::entities::enemies::special_chance(
                    0.05F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                    ));
          }),
      _pos.get(),
      _load_context.model_size(sanguis::load::model::enemy_path(_enemy_type)));
}
