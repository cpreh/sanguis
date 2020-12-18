#ifndef SANGUIS_SERVER_WORLD_SIGHT_RANGE_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_SIGHT_RANGE_MAP_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sanguis/server/world/sight_range_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

using
sight_range_map
=
std::map<
	sanguis::server::player_id,
	sanguis::server::world::sight_range
>;

}
}
}

#endif
