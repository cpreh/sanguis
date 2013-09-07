#ifndef SANGUIS_COLLISION_WORLD_GROUP_VECTOR_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GROUP_VECTOR_HPP_INCLUDED

#include <sanguis/collision/world/group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

typedef std::vector<
	sanguis::collision::world::group
> group_vector;

}
}
}

#endif
