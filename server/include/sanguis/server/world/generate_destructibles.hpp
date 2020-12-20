#ifndef SANGUIS_SERVER_WORLD_GENERATE_DESTRUCTIBLES_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_GENERATE_DESTRUCTIBLES_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/destructible_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/insert_with_id_pair_container.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::world::insert_with_id_pair_container
generate_destructibles(
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::creator::destructible const &,
	sanguis::server::environment::load_context &, // NOLINT(google-runtime-references)
	sanguis::server::world::difficulty
);

}
}
}

#endif
