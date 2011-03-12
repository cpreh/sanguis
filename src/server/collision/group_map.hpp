#ifndef SANGUIS_SERVER_COLLISION_GROUP_MAP_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GROUP_MAP_HPP_INCLUDED

#include "group.hpp"
#include <sge/collision/group_ptr.hpp>
#include <fcppt/container/map_fwd.hpp>
#include <map>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef fcppt::container::map<
	std::map<
		group::type,
		sge::collision::group_ptr
	>
> group_map;

}
}
}

#endif
