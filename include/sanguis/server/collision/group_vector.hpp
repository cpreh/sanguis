#ifndef SANGUIS_SERVER_COLLISION_GROUP_VECTOR_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GROUP_VECTOR_HPP_INCLUDED

#include <sanguis/server/collision/group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

typedef std::vector<
	collision::group::type
> group_vector;

}
}
}

#endif
