#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_MAP_HPP_INCLUDED

#include "player_fwd.hpp"
#include "../player_id.hpp"
#include <sge/container/map_fwd.hpp>
#include <map>

namespace sanguis
{
namespace server
{
namespace entities
{

typedef sge::container::map<
	std::map<
		player_id,
		server::entities::player *
	>
> player_map;

}
}
}

#endif
