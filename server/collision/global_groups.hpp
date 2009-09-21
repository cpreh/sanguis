#ifndef SANGUIS_SERVER_COLLISION_GLOBAL_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GLOBAL_GROUPS_HPP_INCLUDED

#include "group_map.hpp"
#include "group.hpp"
#include <sge/collision/world_fwd.hpp>
#include <sge/collision/shapes/base_fwd.hpp>
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

	void
	add_to_group(
		sge::collision::shapes::base_ptr,
		group::type
	) const;
private:
	group_map groups_;
};

}
}
}

#endif
