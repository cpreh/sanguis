#ifndef SANGUIS_SERVER_AURAS_COLLISION_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_COLLISION_GROUPS_HPP_INCLUDED

#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/auras/influence_fwd.hpp>
#include <sanguis/server/collision/group_vector.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

sanguis::server::collision::group_vector
collision_groups(
	sanguis::server::team,
	sanguis::server::auras::influence
);

}
}
}

#endif
