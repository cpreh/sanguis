#ifndef SANGUIS_COLLISION_AUX__WORLD_SIMPLE_BODY_LIST_GRID_FWD_HPP_INCLUDED
#define SANGUIS_COLLISION_AUX__WORLD_SIMPLE_BODY_LIST_GRID_FWD_HPP_INCLUDED

#include <sanguis/collision/aux_/world/simple/body_list.hpp>
#include <fcppt/container/grid/object_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace aux_
{
namespace world
{
namespace simple
{

typedef
fcppt::container::grid::object<
	sanguis::collision::aux_::world::simple::body_list,
	2
>
body_list_grid;

}
}
}
}
}

#endif
