#include <sanguis/client/draw2d/scene/world/tile_orientation.hpp>
#include <sanguis/client/draw2d/scene/world/to_tile_texture.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/load/tiles/context.hpp>
#include <sanguis/load/tiles/orientation.hpp>
#include <sanguis/load/tiles/set.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>


sge::texture::const_part_shared_ptr
sanguis::client::draw2d::scene::world::to_tile_texture(
	sanguis::load::tiles::context &_tiles,
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const &_pos
)
{
	sanguis::creator::tile const tile(
		_grid[
			_pos
		]
	);

	sanguis::load::tiles::set const &set(
		_tiles.set(
			tile
		)
	);

	sge::texture::const_part_shared_ptr const best_match(
		set.orientation(
			sanguis::client::draw2d::scene::world::tile_orientation(
				_grid,
				_pos
			)
		)
	);

	return
		best_match
		?
			best_match
		:
			set.orientation(
				sanguis::load::tiles::orientation::null()
			)
		;
}
