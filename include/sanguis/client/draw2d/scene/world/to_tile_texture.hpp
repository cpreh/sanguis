#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/tile_orientation.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/load/tiles/context.hpp>
#include <sanguis/load/tiles/orientation.hpp>
#include <sanguis/load/tiles/set.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>


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
sge::texture::const_part_shared_ptr
to_tile_texture(
	sanguis::load::tiles::context &_tiles,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::creator::pos const _pos
)
{
	Tile const tile(
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

}
}
}
}
}

#endif
