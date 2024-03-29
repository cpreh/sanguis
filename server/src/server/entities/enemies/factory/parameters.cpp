#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/enemy_kind.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/entities/enemies/factory/parameters.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/common_parameters.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::entities::enemies::factory::parameters::parameters(
    sanguis::random_generator_ref const _random_generator,
    sanguis::server::weapons::common_parameters const &_weapon_parameters,
    sanguis::creator::enemy_type const _enemy_type,
    sanguis::creator::enemy_kind const _enemy_kind,
    sanguis::server::entities::enemies::difficulty const _difficulty,
    sanguis::server::environment::load_context &_load_context,
    sanguis::server::entities::spawn_owner _spawn_owner,
    sanguis::server::entities::enemies::special_chance const _special_chance)
    : random_generator_(_random_generator),
      weapon_parameters_{_weapon_parameters},
      enemy_type_(_enemy_type),
      enemy_kind_{_enemy_kind},
      difficulty_(_difficulty),
      load_context_(_load_context),
      spawn_owner_(std::move(_spawn_owner)),
      special_chance_(_special_chance)
{
}

sanguis::random_generator &
sanguis::server::entities::enemies::factory::parameters::random_generator() const
{
  return random_generator_.get();
}

sanguis::server::weapons::common_parameters const &
sanguis::server::entities::enemies::factory::parameters::weapon_parameters() const
{
  return weapon_parameters_;
}

sanguis::creator::enemy_type
sanguis::server::entities::enemies::factory::parameters::enemy_type() const
{
  return enemy_type_;
}

sanguis::creator::enemy_kind
sanguis::server::entities::enemies::factory::parameters::enemy_kind() const
{
  return enemy_kind_;
}

sanguis::server::entities::enemies::difficulty
sanguis::server::entities::enemies::factory::parameters::difficulty() const
{
  return difficulty_;
}

sanguis::server::environment::load_context &
sanguis::server::entities::enemies::factory::parameters::load_context() const
{
  return load_context_.get();
}

sanguis::server::entities::spawn_owner const &
sanguis::server::entities::enemies::factory::parameters::spawn_owner() const
{
  return spawn_owner_;
}

sanguis::server::entities::enemies::special_chance
sanguis::server::entities::enemies::factory::parameters::special_chance() const
{
  return special_chance_;
}
