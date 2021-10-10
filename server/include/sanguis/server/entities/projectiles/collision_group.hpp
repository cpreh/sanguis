#ifndef SANGUIS_SERVER_ENTITIES_PROJECTILES_COLLISION_GROUP_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PROJECTILES_COLLISION_GROUP_HPP_INCLUDED

#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>

namespace sanguis::server::entities::projectiles
{

sanguis::collision::world::body_group collision_group(sanguis::server::team);

}

#endif
