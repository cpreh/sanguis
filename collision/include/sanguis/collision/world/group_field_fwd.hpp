#ifndef SANGUIS_COLLISION_WORLD_GROUP_FIELD_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_GROUP_FIELD_FWD_HPP_INCLUDED

#include <sanguis/collision/world/group.hpp>
#include <fcppt/container/bitfield/object_from_enum.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

typedef fcppt::container::bitfield::object_from_enum<
	sanguis::collision::world::group
> group_field;

}
}
}

#endif
