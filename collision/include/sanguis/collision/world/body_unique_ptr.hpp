#ifndef SANGUIS_COLLISION_WORLD_BODY_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_UNIQUE_PTR_HPP_INCLUDED

#include <sanguis/collision/world/body_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sanguis::collision::world
{

using
body_unique_ptr
=
fcppt::unique_ptr<
	sanguis::collision::world::body
>;

}

#endif
