#ifndef SANGUIS_COLLISION_IMPL_WORLD_BODY_GHOST_GROUP_PAIR_GHOST_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_BODY_GHOST_GROUP_PAIR_GHOST_HPP_INCLUDED

#include <fcppt/mpl/list/at.hpp>
#include <fcppt/mpl/size_type.hpp>

namespace sanguis::collision::impl::world
{

template <typename Pair>
using body_ghost_group_pair_ghost = fcppt::mpl::list::at<Pair, fcppt::mpl::size_type<1>>;
}

#endif
