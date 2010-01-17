#ifndef SANGUIS_SERVER_COLLISION_ASSIGN_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_ASSIGN_GROUPS_HPP_INCLUDED

#include "group_vector.hpp"
#include "global_groups_fwd.hpp"
#include <sge/collision/shapes/container.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

sge::collision::shapes::container const
assign_groups(
	sge::collision::shapes::container const &,
	group_vector const &,
	global_groups const &
);

}
}
}

#endif
