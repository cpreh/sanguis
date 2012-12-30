#ifndef SANGUIS_SERVER_ENTITIES_COLLISION_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_COLLISION_GROUPS_HPP_INCLUDED

#include <sanguis/entity_type_fwd.hpp>
#include <sanguis/server/team_fwd.hpp>
#include <sanguis/server/collision/group_vector.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

sanguis::server::collision::group_vector const
collision_groups(
	sanguis::entity_type,
	sanguis::server::team
);

}
}
}

#endif
