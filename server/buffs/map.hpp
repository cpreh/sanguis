#ifndef SANGUIS_SERVER_MAPS_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_MAPS_MAP_HPP_INCLUDED

#include "buff_fwd.hpp"
#include "../../entity_id.hpp"
#include <boost/ptr_container/ptr_map.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

typedef boost::ptr_map<
	entity_id,
	buff
> map;

}
}
}

#endif
