#include <sanguis/client/draw/debug.hpp>
#include <sanguis/client/draw2d/scene/world/log_tile_error.hpp>
#include <sanguis/client/draw2d/scene/world/to_non_connecting_tile_texture.hpp>
#include <sanguis/client/draw2d/scene/world/to_tile_texture_base.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/load/tiles/orientation.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sanguis/client/load/tiles/tile_pair.hpp>
#include <sanguis/client/load/tiles/to_name.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_connects.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>


sge::texture::const_optional_part_ref const
sanguis::client::draw2d::scene::world::to_non_connecting_tile_texture(
	sanguis::client::load::tiles::context &_tiles,
	sanguis::client::draw::debug const _debug,
	sanguis::creator::tile const _tile
)
{
	return
		_tile
		==
		sanguis::creator::tile::nothing
		||
		sanguis::creator::tile_connects(
			_tile
		)
		?
			sge::texture::const_optional_part_ref{}
		:
			sanguis::client::draw2d::scene::world::to_tile_texture_base(
				_tiles.set(
					sanguis::client::load::tiles::tile_pair(
						_tile,
						_tile
					)
				).orientation(
					sanguis::client::load::tiles::orientation::null()
				),
				_debug,
				_tiles.missing_object_texture(),
				[
					_tile
				]
				{
					SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_LOG_TILE_ERROR(
						fcppt::log::_
							<< FCPPT_TEXT("No texture for single tile ")
							<< sanguis::client::load::tiles::to_name(
								_tile
							)
					);
				}
			)
		;
}
