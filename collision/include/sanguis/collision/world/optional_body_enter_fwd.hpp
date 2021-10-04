#ifndef SANGUIS_COLLISION_WORLD_OPTIONAL_BODY_ENTER_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_OPTIONAL_BODY_ENTER_FWD_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sanguis::collision::world
{

using
optional_body_enter
=
fcppt::optional::object<
	sanguis::collision::world::body_enter
>;

}

#endif
