#ifndef SANGUIS_SERVER_AURA_COLLISION_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_AURA_COLLISION_GROUPS_HPP_INCLUDED

#include "influence.hpp"
#include "../team.hpp"
#include "../collision/group_vector.hpp"

namespace sanguis
{
namespace server
{
namespace auras
{

collision::group_vector const
collision_groups(
	team::type,
	influence::type
);

}
}
}

#endif
