#ifndef SANGUIS_COLLISION_WORLD_OBJECT_REF_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_OBJECT_REF_HPP_INCLUDED

#include <sanguis/collision/world/object_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::collision::world
{

using
object_ref
=
fcppt::reference<
	sanguis::collision::world::object
>;

}

#endif
