#ifndef SANGUIS_SERVER_ENTITIES_COLLISION_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_COLLISION_GROUPS_HPP_INCLUDED

#include "../../entity_type.hpp"
#include "../team.hpp"
#include "../collision/group_vector.hpp"

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
