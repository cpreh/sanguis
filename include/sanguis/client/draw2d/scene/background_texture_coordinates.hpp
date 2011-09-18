#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_TEXTURE_COORDINATES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_TEXTURE_COORDINATES_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/client/texture_coordinates.hpp>
#include <sanguis/client/draw2d/vector2.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/texture/part_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{

sprite::client::texture_coordinates const
background_texture_coordinates(
	draw2d::vector2 const &translation,
	sge::renderer::device &,
	sge::texture::part const &
);

}
}
}
}

#endif
