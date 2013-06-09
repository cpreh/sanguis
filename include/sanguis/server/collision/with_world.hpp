#ifndef SANGUIS_SERVER_COLLISION_WITH_WORLD_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_WITH_WORLD_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/collision/optional_result_fwd.hpp>
#include <sanguis/server/entities/base_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

sanguis::server::collision::optional_result const
with_world(
	sanguis::server::entities::base const &,
	sanguis::creator::grid const &,
	sanguis::duration const &
);

}
}
}

#endif
