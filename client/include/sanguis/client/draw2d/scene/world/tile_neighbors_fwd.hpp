#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_NEIGHBORS_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_NEIGHBORS_FWD_HPP_INCLUDED

#include <sanguis/client/load/tiles/direction_fwd.hpp>
#include <fcppt/container/enum_array_fwd.hpp>


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

template<
	typename Tile
>
using
tile_neighbors
=
fcppt::container::enum_array<
	sanguis::client::load::tiles::direction,
	Tile
>;

}
}
}
}
}

#endif
