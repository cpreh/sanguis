#ifndef SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_RANDOM_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/server/difficulty.hpp>
#include <sanguis/server/world/object_unique_ptr.hpp>
#include <sanguis/server/world/parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

sanguis::server::world::object_unique_ptr
random(
	sanguis::server::world::parameters const &,
	sanguis::creator::opening_count,
	sanguis::world_id,
	sanguis::server::difficulty
);

}
}
}

#endif
