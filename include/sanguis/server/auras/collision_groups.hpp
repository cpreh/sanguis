#ifndef SANGUIS_SERVER_AURAS_COLLISION_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_COLLISION_GROUPS_HPP_INCLUDED

#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/collision/group_vector.hpp>

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
