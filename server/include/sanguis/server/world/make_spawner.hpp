#ifndef SANGUIS_SERVER_WORLD_MAKE_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_MAKE_SPAWNER_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/world/difficulty.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::entities::unique_ptr
make_spawner(
	sanguis::creator::enemy_type,
	sanguis::diff_clock const &,
	sanguis::random_generator &,
	sanguis::server::world::difficulty
);

}
}
}

#endif
