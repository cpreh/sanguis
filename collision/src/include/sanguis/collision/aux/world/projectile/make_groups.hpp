#ifndef SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_MAKE_GROUPS_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX_WORLD_PROJECTILE_MAKE_GROUPS_HPP_INCLUDED

#include <sanguis/collision/aux/world/projectile/global_groups_fwd.hpp>
#include <sanguis/collision/world/group_vector.hpp>
#include <sge/projectile/group/sequence.hpp>


namespace sanguis
{
namespace collision
{
namespace aux
{
namespace world
{
namespace projectile
{

sge::projectile::group::sequence const
make_groups(
	sanguis::collision::world::group_vector const &,
	sanguis::collision::aux::world::projectile::global_groups const &
);

}
}
}
}
}

#endif
