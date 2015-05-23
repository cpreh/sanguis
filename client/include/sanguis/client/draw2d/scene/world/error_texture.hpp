#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_ERROR_TEXTURE_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_WORLD_ERROR_TEXTURE_HPP_INCLUDED

#include <sanguis/client/load/tiles/context_fwd.hpp>
#include <sanguis/tiles/error_fwd.hpp>
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

sge::texture::part const &
error_texture(
	sanguis::client::load::tiles::context &,
	sanguis::tiles::error
);

}
}
}
}
}

#endif

