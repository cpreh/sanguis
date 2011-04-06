#ifndef SANGUIS_SERVER_WORLD_ENTITY_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENTITY_MAP_HPP_INCLUDED

#include "../../entity_id.hpp"
#include "../entities/base_fwd.hpp"
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{
namespace world
{

typedef boost::ptr_map<
	sanguis::entity_id,
	entities::base
> entity_map;

}
}
}

#endif
