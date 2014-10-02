#ifndef SANGUIS_SERVER_AURAS_COLLISION_GROUP_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_COLLISION_GROUP_HPP_INCLUDED

#include <sanguis/collision/world/ghost_group_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/influence_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

sanguis::collision::world::ghost_group
collision_group(
	sanguis::server::team,
	sanguis::server::auras::influence
);

}
}
}

#endif
