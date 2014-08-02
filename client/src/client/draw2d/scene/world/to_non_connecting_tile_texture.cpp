#include <sanguis/client/draw2d/scene/world/log_tile_error.hpp>
#include <sanguis/client/draw2d/scene/world/to_non_connecting_tile_texture.hpp>
#include <sanguis/client/load/tiles/const_optional_texture_container_ref.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/client/load/tiles/orientation.hpp>
#include <sanguis/client/load/tiles/set.hpp>
#include <sanguis/client/load/tiles/tile_pair.hpp>
#include <sanguis/client/load/tiles/to_name.hpp>
#include <sanguis/creator/tile.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>


sge::texture::const_part_shared_ptr
sanguis::client::draw2d::scene::world::to_non_connecting_tile_texture(
	sanguis::client::load::tiles::context &_tiles,
	sanguis::creator::tile const _tile
)
{
	sanguis::client::load::tiles::const_optional_texture_container_ref const container(
		_tiles.set(
			sanguis::client::load::tiles::tile_pair(
				_tile,
				_tile
			)
		).orientation(
			sanguis::client::load::tiles::orientation::null()
		)
	);

	// TODO: Put this in a function?
	if(
		!container
		||
		container->empty()
	)
	{
		SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_LOG_TILE_ERROR(
			fcppt::log::_
				<< FCPPT_TEXT("No texture for single tile ")
				<< sanguis::client::load::tiles::to_name(
					_tile
				)
		);

		return
			sge::texture::const_part_shared_ptr();
	}

	// TODO: Make this random
	return
		container->at(
			0
		);
}
