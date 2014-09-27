#ifndef SANGUIS_COLLISION_AUX__WORLD_GROUP_PAIR_STATIC_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_GROUP_PAIR_STATIC_HPP_INCLUDED

#include <sanguis/collision/world/group.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/pair.hpp>
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
	sanguis::collision::world::group Group1,
	sanguis::collision::world::group Group2
>
using
group_pair_static
=
boost::mpl::pair<
	boost::mpl::integral_c<
		sanguis::collision::world::group,
		Group1
	>,
	boost::mpl::integral_c<
		sanguis::collision::world::group,
		Group2
	>
>;

}
}
}
}

#endif
