#ifndef SANGUIS_SERVER_WORLD_MAKE_DESTRUCTIBLE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_MAKE_DESTRUCTIBLE_HPP_INCLUDED

#include <sanguis/creator/destructible_type_fwd.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>

namespace sanguis::server::world
{

sanguis::server::entities::with_id_unique_ptr make_destructible(
    sanguis::creator::destructible_type,
    sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
    sanguis::server::world::difficulty);

}

#endif
