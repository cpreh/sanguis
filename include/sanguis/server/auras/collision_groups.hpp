#ifndef SANGUIS_SERVER_AURAS_COLLISION_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_COLLISION_GROUPS_HPP_INCLUDED

#include <sanguis/collision/world/group_field_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/influence_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

sanguis::collision::world::group_field const
collision_groups(
	sanguis::server::team,
	sanguis::server::auras::influence
);

}
}
}

#endif
