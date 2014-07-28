#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/make_tile_neighbors.hpp>
#include <sanguis/client/draw2d/scene/world/make_tile_pair.hpp>
#include <sanguis/client/draw2d/scene/world/tile_neighbors.hpp>
#include <sanguis/client/draw2d/scene/world/tile_orientation.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/client/load/tiles/const_optional_texture_container_ref.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/load/tiles/optional_pair.hpp>
#include <sanguis/client/load/tiles/orientation.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sanguis/client/load/tiles/texture_container.hpp>
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
	sanguis::client::load::tiles::context &_tiles,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::creator::pos const _pos
)
{
	sanguis::client::draw2d::scene::world::tile_neighbors<
		Tile
	> const tiles(
		sanguis::client::draw2d::scene::world::make_tile_neighbors(
			_grid,
			_pos
		)
	);

	sanguis::client::load::tiles::optional_pair<
		Tile
	> const pair(
		sanguis::client::draw2d::scene::world::make_tile_pair(
			tiles
		)
	);

	// TODO: Warning? Error?
	if(
		!pair
	)
		return
			sge::texture::const_part_shared_ptr();

	sanguis::client::load::tiles::set const &set(
		_tiles.set(
			*pair
		)
	);

	sanguis::client::load::tiles::const_optional_texture_container_ref const textures(
		set.orientation(
			sanguis::client::draw2d::scene::world::tile_orientation(
				*pair,
				tiles
			)
		)
	);

	// TODO: Warning? Error?
	if(
		!textures
		||
		textures->empty()
	)
		return
			sge::texture::const_part_shared_ptr();

	// TODO: Make this random
	return
		textures->at(
			0u
		);
}

}
}
}
}
}

#endif
