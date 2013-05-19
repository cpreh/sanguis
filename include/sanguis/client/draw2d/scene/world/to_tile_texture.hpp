#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_TO_TILE_TEXTURE_HPP_INCLUDED

#include <sanguis/creator/tile_fwd.hpp>
#include <sanguis/load/resource/textures_fwd.hpp>
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

sge::texture::const_part_shared_ptr
to_tile_texture(
	sanguis::load::resource::textures const &,
	sanguis::creator::tile
);

}
}
}
}
}

#endif
