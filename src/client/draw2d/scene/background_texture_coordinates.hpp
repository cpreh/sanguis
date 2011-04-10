#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_TEXTURE_COORDINATES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_BACKGROUND_TEXTURE_COORDINATES_HPP_INCLUDED

#include "../sprite/client/texture_coordinates.hpp"
#include "../vector2.hpp"
#include <sge/renderer/device_ptr.hpp>
#include <sge/texture/const_part_ptr.hpp>

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
	sge::renderer::device_ptr,
	sge::texture::const_part_ptr
);

}
}
}
}

#endif
