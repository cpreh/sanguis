#ifndef SANGUIS_SERVER_WORLD_MAKE_SPAWNER_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_MAKE_SPAWNER_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_kind_fwd.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/creator/spawn_pos_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/insert_pair.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::world::insert_pair
make_spawner(
	sanguis::creator::enemy_type,
	sanguis::creator::enemy_kind,
	sanguis::creator::spawn_pos,
	sanguis::random_generator &,
	sanguis::server::world::difficulty
);

}
}
}

#endif
