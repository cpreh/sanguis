#ifndef SANGUIS_SERVER_WORLD_GENERATE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_GENERATE_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/server/world/difficulty.hpp>
#include <sanguis/server/world/object_unique_ptr.hpp>
#include <sanguis/server/world/parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::world::object_unique_ptr
generate(
	sanguis::server::world::parameters const &,
	sanguis::creator::opening_count,
	sanguis::world_id,
	sanguis::creator::name const &,
	sanguis::creator::seed,
	sanguis::world_name const &,
	sanguis::server::world::difficulty
);

}
}
}

#endif
