#ifndef SANGUIS_COLLISION_AUX__WORLD_BODY_GROUP_CONTAINER_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_BODY_GROUP_CONTAINER_HPP_INCLUDED

#include <sanguis/collision/world/body_group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{

typedef
std::vector<
	sanguis::collision::world::body_group
>
body_group_container;

}
}
}
}

#endif
