#ifndef SANGUIS_SERVER_WORLD_CAN_BE_SPAWNED_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_CAN_BE_SPAWNED_HPP_INCLUDED

#include <sanguis/server/entities/base_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace world
{

bool
can_be_spawned(
	sge::projectile::world const &,
	sge::projectile::body::object const &,
	sanguis::server::entities::base const &
);

}
}
}

#endif
