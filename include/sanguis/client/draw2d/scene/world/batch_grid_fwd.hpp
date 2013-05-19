#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_GRID_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_GRID_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/batch_fwd.hpp>
#include <fcppt/container/grid/object_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace world
{

typedef fcppt::container::grid::object<
	sanguis::client::draw2d::scene::world::batch,
	2
> batch_grid;

}
}
}
}
}

#endif
