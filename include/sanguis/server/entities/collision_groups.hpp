#ifndef SANGUIS_SERVER_ENTITIES_COLLISION_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_COLLISION_GROUPS_HPP_INCLUDED

#include <sanguis/server/team.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/entity_type.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

collision::group_vector const
collision_groups(
	entity_type::type,
	team::type
);

}
}
}

#endif
