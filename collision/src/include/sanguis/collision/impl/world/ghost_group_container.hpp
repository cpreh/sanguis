#ifndef SANGUIS_COLLISION_IMPL_WORLD_GHOST_GROUP_CONTAINER_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_GHOST_GROUP_CONTAINER_HPP_INCLUDED

#include <sanguis/collision/world/ghost_group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
{

typedef
std::vector<
	sanguis::collision::world::ghost_group
>
ghost_group_container;

}
}
}
}

#endif
