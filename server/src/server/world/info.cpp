#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_boss.hpp>
#include <sanguis/server/world/info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::world::info::info(
    sanguis::world_id const _world_id,
    sanguis::world_name &&_world_name,
    sanguis::creator::seed const _seed,
    sanguis::creator::name &&_generator_name,
    sanguis::creator::spawn_boss const _spawn_boss,
    sanguis::creator::opening_container_array &&_openings)
    : world_id_(_world_id),
      world_name_(std::move(_world_name)),
      seed_(_seed),
      generator_name_(std::move(_generator_name)),
      spawn_boss_(_spawn_boss),
      openings_(std::move(_openings))
{
}

sanguis::world_id sanguis::server::world::info::world_id() const { return world_id_; }

sanguis::world_name const &sanguis::server::world::info::world_name() const { return world_name_; }

sanguis::creator::seed sanguis::server::world::info::seed() const { return seed_; }

sanguis::creator::name const &sanguis::server::world::info::generator_name() const
{
  return generator_name_;
}

sanguis::creator::spawn_boss sanguis::server::world::info::spawn_boss() const
{
  return spawn_boss_;
}

sanguis::creator::opening_container_array const &sanguis::server::world::info::openings() const
{
  return openings_;
}
