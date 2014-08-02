#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILTER_TILE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_FILTER_TILE_HPP_INCLUDED

#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_connects.hpp>


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
sanguis::creator::tile
filter_tile(
	sanguis::creator::tile const _tile
)
{
	return
		sanguis::creator::tile_connects(
			_tile
		)
		?
			_tile
		:
			sanguis::creator::tile::nothing
		;
}

inline
sanguis::creator::background_tile
filter_tile(
	sanguis::creator::background_tile const _tile
)
{
	return
		_tile;
}

}
}
}
}
}

#endif
