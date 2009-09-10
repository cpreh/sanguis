#ifndef SANGUIS_SERVER_WORLD_ENTITY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENTITY_MAP_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../entities/entity_fwd.hpp"
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

typedef boost::ptr_map<
	entity_id,
	entities::entity
> entity_map;

}
}
}

#endif
