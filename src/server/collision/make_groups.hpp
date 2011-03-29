#ifndef SANGUIS_SERVER_COLLISION_MAKE_GROUPS_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_MAKE_GROUPS_HPP_INCLUDED

#include "group_vector.hpp"
#include "global_groups_fwd.hpp"
#include <sge/projectile/group/sequence.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

sge::projectile::group::sequence const
make_groups(
	collision::group_vector const &,
	collision::global_groups const &
);

}
}
}

#endif
