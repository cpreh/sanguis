#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED

#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/log.hpp>
#include <sanguis/client/draw2d/scene/world/filter_tile_pair.hpp>
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
#include <sanguis/client/load/tiles/orientation.hpp>
#include <sanguis/client/load/tiles/pair.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>


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
	sanguis::client::draw::debug const _debug,
	sanguis::creator::tile_grid<
		Tile
	> const &_grid,
	sanguis::creator::pos const _pos
)
{
	sanguis::client::draw2d::scene::world::tile_neighbors<
		Tile
	> const neighbors(
		sanguis::client::draw2d::scene::world::make_tile_neighbors(
			_grid,
			_pos
		)
	);

	return
		fcppt::maybe(
			sanguis::client::draw2d::scene::world::make_tile_pair(
				neighbors
			),
			[
				&neighbors
			]
			{
				FCPPT_LOG_ERROR(
					sanguis::client::draw2d::log(),
					fcppt::log::_
						<< FCPPT_TEXT("Tile combination ")
						<< sanguis::client::draw2d::scene::world::tile_neighbors_to_string(
							neighbors
						)
						<< FCPPT_TEXT(" consists of too many tiles.")
				);

				return
					sge::texture::const_optional_part_ref{};
			},
			[
				&_tiles,
				&neighbors,
				_debug
			](
				sanguis::client::load::tiles::pair<
					Tile
				> const _pair
			)
			{
				return
					sanguis::client::draw2d::scene::world::filter_tile_pair(
						_pair
					)
					?
						sge::texture::const_optional_part_ref{}
					:
						sanguis::client::draw2d::scene::world::to_tile_texture_base(
							_tiles.set(
								_pair
							).orientation(
								sanguis::client::draw2d::scene::world::tile_orientation(
									_pair,
									neighbors
								)
							),
							_debug,
							sanguis::client::draw2d::scene::world::missing_tile_texture<
								Tile
							>::get(
								_tiles
							),
							[
								&neighbors
							]
							{
								SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_LOG_TILE_ERROR(
									fcppt::log::_
										<< FCPPT_TEXT("No texture for tile combation ")
										<< sanguis::client::draw2d::scene::world::tile_neighbors_to_string(
											neighbors
										)
								);
							}
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
