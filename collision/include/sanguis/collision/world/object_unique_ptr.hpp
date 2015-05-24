#ifndef SANGUIS_COLLISION_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/collision/world/object_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis
{
namespace collision
{
namespace world
{

typedef
fcppt::unique_ptr<
	sanguis::collision::world::object
>
object_unique_ptr;

}
}
}

#endif
