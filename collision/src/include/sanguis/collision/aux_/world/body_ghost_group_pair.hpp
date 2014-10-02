#ifndef SANGUIS_COLLISION_AUX__WORLD_BODY_GHOST_GROUP_PAIR_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_BODY_GHOST_GROUP_PAIR_HPP_INCLUDED

#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/pair.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{

template<
	sanguis::collision::world::body_group Group1,
	sanguis::collision::world::ghost_group Group2
>
using
body_ghost_group_pair
=
boost::mpl::pair<
	std::integral_constant<
		sanguis::collision::world::body_group,
		Group1
	>,
	std::integral_constant<
		sanguis::collision::world::ghost_group,
		Group2
	>
>;

}
}
}
}

#endif
