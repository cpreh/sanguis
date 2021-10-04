#ifndef SANGUIS_COLLISION_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_OBJECT_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/collision/world/object_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::collision::world
{

using
object_unique_ptr
=
fcppt::unique_ptr<
	sanguis::collision::world::object
>;

}

#endif
