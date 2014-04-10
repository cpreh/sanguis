#ifndef SANGUIS_SERVER_COLLISION_WITH_WORLD_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_WITH_WORLD_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/dim_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

bool
with_world(
	sanguis::server::center,
	sanguis::server::dim,
	sanguis::creator::grid const &
);

}
}
}

#endif
