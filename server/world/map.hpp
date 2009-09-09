#ifndef SANGUIS_SERVER_WORLD_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_MAP_HPP_INCLUDED

#include "world_fwd.hpp"
#include "../../world_id.hpp"

namespace sanguis
{
namespace server
{
namespace world
{

typedef boost::ptr_map<
	world_id,
	object
> map;

}
}
}

#endif
