#ifndef SANGUIS_COLLISION_WORLD_BODY_ENTER_CONTAINER_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_ENTER_CONTAINER_HPP_INCLUDED

#include <sanguis/collision/world/body_enter.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

typedef
std::vector<
	sanguis::collision::world::body_enter
>
body_enter_container;

}
}
}

#endif
