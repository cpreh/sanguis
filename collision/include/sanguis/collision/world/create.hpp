#ifndef SANGUIS_COLLISION_WORLD_CREATE_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_CREATE_HPP_INCLUDED

#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/object_unique_ptr.hpp>
#include <sanguis/collision/world/parameters_fwd.hpp>


namespace sanguis::collision::world
{

SANGUIS_COLLISION_SYMBOL
sanguis::collision::world::object_unique_ptr
create(
	sanguis::collision::world::parameters const &
);

}

#endif
