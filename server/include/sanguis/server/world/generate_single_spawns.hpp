#ifndef SANGUIS_SERVER_WORLD_GENERATE_SINGLE_SPAWNS_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_GENERATE_SINGLE_SPAWNS_HPP_INCLUDED

#include <sanguis/random_generator_ref.hpp>
#include <sanguis/creator/enemy_kind_fwd.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/creator/spawn_pos_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/insert_with_id_pair_container.hpp>

namespace sanguis::server::world
{

sanguis::server::world::insert_with_id_pair_container generate_single_spawns(
    sanguis::creator::enemy_type,
    sanguis::creator::enemy_kind,
    sanguis::creator::spawn_pos const &,
    sanguis::server::weapons::common_parameters const &,
    sanguis::random_generator_ref,
    sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
    sanguis::server::world::difficulty);

}

#endif
