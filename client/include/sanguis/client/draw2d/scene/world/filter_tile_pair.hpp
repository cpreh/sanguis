#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILTER_TILE_PAIR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILTER_TILE_PAIR_HPP_INCLUDED

#include <sanguis/client/load/tiles/background_tile_pair.hpp>
#include <sanguis/client/load/tiles/tile_pair.hpp>
#include <sanguis/creator/tile.hpp>


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

inline
bool
filter_tile_pair(
	sanguis::client::load::tiles::tile_pair const _pair
)
{
	return
		_pair.first
		==
		sanguis::creator::tile::nothing
		&&
		_pair.second
		==
		sanguis::creator::tile::nothing;
}

inline
bool
filter_tile_pair(
	sanguis::client::load::tiles::background_tile_pair
)
{
	return
		false;
}

}
}
}
}
}

#endif
