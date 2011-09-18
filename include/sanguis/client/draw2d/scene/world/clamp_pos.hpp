#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_POS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_CLAMP_POS_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/batch_grid.hpp>
#include <sanguis/client/draw2d/scene/world/batch.hpp>
#include <sanguis/client/draw2d/scene/world/signed_pos.hpp>
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

world::batch_grid::dim const
clamp_pos(
	world::signed_pos const &pos,
	world::batch_grid::dim const &size
);

}
}
}
}
}

#endif
