#ifndef SANGUIS_SERVER_COLLISION_GLOBAL_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GLOBAL_GROUPS_HPP_INCLUDED

#include "group_map.hpp"
#include <sge/collision/world_fwd.hpp>
#include <sge/container/map_decl.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class global_groups {
public:
	explicit global_groups(
		sge::collision::world_ptr
	);
private:
	group_map groups_;
};

}
}
}

#endif
