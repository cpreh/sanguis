#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_POS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_POS_HPP_INCLUDED

#include "batch_grid.hpp"
#include "batch.hpp"
#include <fcppt/container/grid/object_decl.hpp>
#include <fcppt/math/dim/basic_decl.hpp>

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

batch_grid::dim const
clamp_pos(
	batch_grid::dim const &pos,
	batch_grid::dim const &size
);

}
}
}
}
}

#endif
