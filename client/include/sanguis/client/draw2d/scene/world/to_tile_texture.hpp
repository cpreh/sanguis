#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/debug.hpp>
#include <sanguis/client/draw2d/scene/world/log_tile_error.hpp>
#include <sanguis/client/draw2d/scene/world/make_tile_neighbors.hpp>
#include <sanguis/client/draw2d/scene/world/make_tile_pair.hpp>
#include <sanguis/client/draw2d/scene/world/missing_tile_texture.hpp>
#include <sanguis/client/draw2d/scene/world/tile_neighbors.hpp>
#include <sanguis/client/draw2d/scene/world/tile_neighbors_to_string.hpp>
#include <sanguis/client/draw2d/scene/world/tile_orientation.hpp>
#include <sanguis/client/draw2d/scene/world/to_tile_texture_base.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_grid.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/load/tiles/optional_pair.hpp>
#include <sanguis/client/load/tiles/orientation.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <fcppt/log/_.hpp>


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
sge::texture::const_optional_part_ref const
to_tile_texture(
	sanguis::client::load::tiles::context &_tiles,
	sanguis::client::draw2d::scene::world::debug const _debug,
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

	if(
		!pair
	)
	{
		SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_LOG_TILE_ERROR(
			fcppt::log::_
				<< FCPPT_TEXT("Tile combination ")
				<< sanguis::client::draw2d::scene::world::tile_neighbors_to_string(
					tiles
				)
				<< FCPPT_TEXT(" not available.")
		);

		return
			sge::texture::const_optional_part_ref{};
	}

	return
		sanguis::client::draw2d::scene::world::to_tile_texture_base(
			_tiles.set(
				*pair
			).orientation(
				sanguis::client::draw2d::scene::world::tile_orientation(
					*pair,
					tiles
				)
			),
			_debug,
			sanguis::client::draw2d::scene::world::missing_tile_texture<
				Tile
			>::get(
				_tiles
			),
			[
				tiles
			]
			{
				SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_LOG_TILE_ERROR(
					fcppt::log::_
						<< FCPPT_TEXT("No texture for tile combation ")
						<< sanguis::client::draw2d::scene::world::tile_neighbors_to_string(
							tiles
						)
				);
			}
		);
}

}
}
}
}
}

#endif
