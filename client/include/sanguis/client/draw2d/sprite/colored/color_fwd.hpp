#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_COLOR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_COLOR_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/colored/color_format.hpp>
#include <sge/image/pixel/mizuiro_type_fwd.hpp>

namespace sanguis::client::draw2d::sprite::colored
{

using color =
    sge::image::pixel::mizuiro_type<sanguis::client::draw2d::sprite::colored::color_format>;

}

#endif
