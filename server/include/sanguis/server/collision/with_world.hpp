#ifndef SANGUIS_SERVER_COLLISION_WITH_WORLD_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_WITH_WORLD_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/radius_fwd.hpp>


namespace sanguis::server::collision
{

bool
with_world(
	sanguis::server::center const &,
	sanguis::server::radius,
	sanguis::creator::grid const &
);

}

#endif
