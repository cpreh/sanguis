#ifndef SANGUIS_COLLISION_AUX__WORLD_GROUP_PAIR_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_GROUP_PAIR_FWD_HPP_INCLUDED

#include <sanguis/collision/world/group_fwd.hpp>
#include <fcppt/homogenous_pair_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{

typedef
fcppt::homogenous_pair<
	sanguis::collision::world::group
>
group_pair;

}
}
}
}

#endif
