#ifndef SANGUIS_COLLISION_WORLD_BODY_COLLISION_CONTAINER_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_COLLISION_CONTAINER_HPP_INCLUDED

#include <sanguis/collision/world/body_collision.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

using
body_collision_container
=
std::vector<
	sanguis::collision::world::body_collision
>;

}
}
}

#endif
