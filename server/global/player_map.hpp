#ifndef SANGUIS_SERVER_GLOBAL_PLAYER_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_GLOBAL_PLAYER_MAP_HPP_INCLUDED

#include "../player_id.hpp"
#include "../entities/player_fwd.hpp"
#include <map>

namespace sanguis
{
namespace server
{
namespace global
{

typedef sge::container::map<
	std::map,
	player_id,
	server::entities::player *
> player_map;

}
}
}

#endif
