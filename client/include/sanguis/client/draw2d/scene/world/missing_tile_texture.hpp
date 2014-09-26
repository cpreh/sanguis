#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MISSING_TILE_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_MISSING_TILE_TEXTURE_HPP_INCLUDED

#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/creator/background_tile_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


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
struct missing_tile_texture;

template<>
struct missing_tile_texture<
	sanguis::creator::tile
>
{
	static
	sge::texture::part const &
	get(
		sanguis::client::load::tiles::context const &
	);
};

template<>
struct missing_tile_texture<
	sanguis::creator::background_tile
>
{
	static
	sge::texture::part const &
	get(
		sanguis::client::load::tiles::context const &
	);
};

}
}
}
}
}

#endif
