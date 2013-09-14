#ifndef SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_MAKE_GROUPS_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_PROJECTILE_MAKE_GROUPS_HPP_INCLUDED

#include <sanguis/collision/aux_/world/projectile/global_groups_fwd.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sge/projectile/group/sequence.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace projectile
{

sge::projectile::group::sequence const
make_groups(
	sanguis::collision::world::group_field const &,
	sanguis::collision::aux_::world::projectile::global_groups const &
);

}
}
}
}
}

#endif
