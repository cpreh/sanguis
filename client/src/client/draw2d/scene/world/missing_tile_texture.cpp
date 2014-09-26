#include <sanguis/client/draw2d/scene/world/missing_tile_texture.hpp>
#include <sanguis/client/load/tiles/context.hpp>
#include <sanguis/creator/background_tile_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


sge::texture::part const &
sanguis::client::draw2d::scene::world::missing_tile_texture<
	sanguis::creator::tile
>::get(
	sanguis::client::load::tiles::context const &_context
)
{
	return
		_context.missing_texture();
}

sge::texture::part const &
sanguis::client::draw2d::scene::world::missing_tile_texture<
	sanguis::creator::background_tile
>::get(
	sanguis::client::load::tiles::context const &_context
)
{
	return
		_context.missing_background_texture();
}
