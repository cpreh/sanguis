#ifndef SANGUIS_SERVER_WORLD_SPAWN_ENTITY_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SPAWN_ENTITY_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/spawn_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::entities::unique_ptr spawn_entity(
    sanguis::creator::spawn const &,
    sanguis::random_generator &,
    sanguis::server::environment::load_context &,
    sanguis::server::world::difficulty);

}
}
}

#endif
