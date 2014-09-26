#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_NON_CONNECTING_TILE_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_NON_CONNECTING_TILE_TEXTURE_HPP_INCLUDED

#include <sanguis/client/draw2d/scene/world/debug.hpp>
#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <sge/texture/const_optional_part_ref.hpp>


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

sge::texture::const_optional_part_ref const
to_non_connecting_tile_texture(
	sanguis::client::load::tiles::context &,
	sanguis::client::draw2d::scene::world::debug,
	sanguis::creator::tile
);

}
}
}
}
}

#endif
