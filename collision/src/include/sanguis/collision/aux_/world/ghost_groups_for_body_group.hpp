#ifndef SANGUIS_COLLISION_AUX__WORLD_GHOST_GROUPS_FOR_BODY_GROUP_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_GHOST_GROUPS_FOR_BODY_GROUP_HPP_INCLUDED

#include <sanguis/collision/aux_/world/ghost_group_container.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{

sanguis::collision::aux_::world::ghost_group_container const &
ghost_groups_for_body_group(
	sanguis::collision::world::body_group
);

}
}
}
}

#endif
