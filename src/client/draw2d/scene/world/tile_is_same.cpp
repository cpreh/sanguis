#include <sanguis/client/draw2d/scene/world/tile_is_same.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>


bool
sanguis::client::draw2d::scene::world::tile_is_same(
	sanguis::creator::tile const _tile,
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const &_pos
)
{
	return
		_pos.w() < _grid.size().w()
		&&
		_pos.h() < _grid.size().h()
		&&
		_grid[
			_pos
		]
		==
		_tile;

}
