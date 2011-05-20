#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_GRID_UNIQUE_PTR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_BATCH_GRID_UNIQUE_PTR_HPP_INCLUDED

#include "batch_grid.hpp"
#include <fcppt/unique_ptr.hpp>

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

typedef fcppt::unique_ptr<
	world::batch_grid
> batch_grid_unique_ptr;

}
}
}
}
}

#endif
