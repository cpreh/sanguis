#ifndef SANGUIS_SERVER_GLOBAL_GENERATE_WORLDS_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_GENERATE_WORLDS_HPP_INCLUDED

#include <sanguis/server/global/world_map.hpp>
#include <sanguis/server/world/parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace global
{

sanguis::server::global::world_map
generate_worlds(
	sanguis::server::world::parameters const &
);

}
}
}

#endif
