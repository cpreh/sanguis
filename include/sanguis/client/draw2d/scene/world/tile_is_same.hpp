#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_IS_SAME_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TILE_IS_SAME_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <fcppt/container/grid/in_range.hpp>


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
bool
tile_is_same(
	Tile const _tile,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::creator::pos const &_pos
)
{
	return
		fcppt::container::grid::in_range(
			_grid,
			_pos
		)
		&&
		_grid[
			_pos
		]
		==
		_tile;
}

}
}
}
}
}

#endif
