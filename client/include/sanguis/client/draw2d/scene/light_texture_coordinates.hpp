#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_LIGHT_TEXTURE_COORDINATES_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_LIGHT_TEXTURE_COORDINATES_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/client/texture_coordinates.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/texture/part_fwd.hpp>


namespace sanguis::client::draw2d::scene
{

sanguis::client::draw2d::sprite::client::texture_coordinates
light_texture_coordinates(
	sge::renderer::device::core &, // NOLINT(google-runtime-references)
	sge::texture::part const &
);

}

#endif
