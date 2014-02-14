#ifndef SANGUIS_SERVER_WORLD_GENERATE_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_GENERATE_HPP_INCLUDED

#include <sanguis/world_id.hpp>
#include <sanguis/world_name.hpp>
#include <sanguis/creator/top_parameters_fwd.hpp>
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
	sanguis::world_id,
	sanguis::world_name const &,
	sanguis::server::world::difficulty,
	sanguis::creator::top_parameters const &
);

}
}
}

#endif
