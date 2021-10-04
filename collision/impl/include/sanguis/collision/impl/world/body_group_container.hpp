#ifndef SANGUIS_COLLISION_IMPL_WORLD_BODY_GROUP_CONTAINER_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_BODY_GROUP_CONTAINER_HPP_INCLUDED

#include <sanguis/collision/world/body_group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis::collision::impl::world
{

using
body_group_container
=
std::vector<
	sanguis::collision::world::body_group
>;

}

#endif
