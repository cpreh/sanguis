#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_ORIENTATION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_ORIENTATION_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/load/tiles/orientation_fwd.hpp>


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

sanguis::load::tiles::orientation const
tile_orientation(
	sanguis::creator::grid const &,
	sanguis::creator::pos const &
);

}
}
}
}
}

#endif
