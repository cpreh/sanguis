#ifndef SANGUIS_COLLISION_WORLD_BODY_BODY_HPP_INCLUDED
#define SANGUIS_COLLISION_WORLD_BODY_BODY_HPP_INCLUDED

#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/optional_result_pair.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/collision/world/body_fwd.hpp>


namespace sanguis::collision::world
{

SANGUIS_COLLISION_SYMBOL
sanguis::collision::optional_result_pair
body_body(
	sanguis::collision::world::body const &,
	sanguis::collision::world::body const &,
	sanguis::collision::duration
);

}

#endif
