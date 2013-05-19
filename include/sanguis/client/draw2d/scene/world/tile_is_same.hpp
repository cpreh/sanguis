#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_IS_SAME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_IS_SAME_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>


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

bool
tile_is_same(
	sanguis::creator::tile,
	sanguis::creator::grid const &,
	sanguis::creator::pos const &
);

}
}
}
}
}

#endif
