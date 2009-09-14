#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_MAP_HPP_INCLUDED

#include "sight_range_fwd.hpp"
#include "../player_id.hpp"
#include <map>

namespace sanguis
{
namespace server
{
namespace world
{

typedef std::map<
	player_id,
	sight_range
> sight_range_map;

}
}
}

#endif