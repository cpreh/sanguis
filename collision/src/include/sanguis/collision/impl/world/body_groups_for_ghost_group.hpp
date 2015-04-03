#ifndef SANGUIS_COLLISION_IMPL_WORLD_BODY_GROUPS_FOR_GHOST_GROUP_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_BODY_GROUPS_FOR_GHOST_GROUP_HPP_INCLUDED

#include <sanguis/collision/impl/world/body_group_container.hpp>
#include <sanguis/collision/world/ghost_group_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
{

sanguis::collision::impl::world::body_group_container const &
body_groups_for_ghost_group(
	sanguis::collision::world::ghost_group
);

}
}
}
}

#endif
