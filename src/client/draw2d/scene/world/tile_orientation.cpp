#include <sanguis/client/draw2d/scene/world/tile_is_same.hpp>
#include <sanguis/client/draw2d/scene/world/tile_orientation.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/load/tiles/direction.hpp>
#include <sanguis/load/tiles/orientation.hpp>


sanguis::load::tiles::orientation const
sanguis::client::draw2d::scene::world::tile_orientation(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const &_pos
)
{
	sanguis::load::tiles::orientation orientation{
		sanguis::load::tiles::orientation::null()
	};

	sanguis::creator::tile const tile(
		_grid[
			_pos
		]
	);

	orientation[
		sanguis::load::tiles::direction::north
	] =
		sanguis::client::draw2d::scene::world::tile_is_same(
			tile,
			_grid,
			sanguis::creator::pos(
				_pos.x(),
				_pos.y() - 1
			)
		);

	orientation[
		sanguis::load::tiles::direction::west
	] =
		sanguis::client::draw2d::scene::world::tile_is_same(
			tile,
			_grid,
			sanguis::creator::pos(
				_pos.x() - 1,
				_pos.y()
			)
		);

	orientation[
		sanguis::load::tiles::direction::east
	] =
		sanguis::client::draw2d::scene::world::tile_is_same(
			tile,
			_grid,
			sanguis::creator::pos(
				_pos.x() + 1,
				_pos.y()
			)
		);

	orientation[
		sanguis::load::tiles::direction::south
	] =
		sanguis::client::draw2d::scene::world::tile_is_same(
			tile,
			_grid,
			sanguis::creator::pos(
				_pos.x(),
				_pos.y() + 1
			)
		);

	return
		orientation;
}
