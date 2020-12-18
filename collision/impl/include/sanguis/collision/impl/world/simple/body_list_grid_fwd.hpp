#ifndef SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_LIST_GRID_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_WORLD_SIMPLE_BODY_LIST_GRID_FWD_HPP_INCLUDED

#include <sanguis/collision/impl/world/simple/body_list.hpp>
#include <fcppt/container/grid/object_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{
namespace world
{
namespace simple
{

using
body_list_grid
=
fcppt::container::grid::object<
	sanguis::collision::impl::world::simple::body_list,
	2
>;

}
}
}
}
}

#endif
