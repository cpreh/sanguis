#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_COLOR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_COLORED_COLOR_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/colored/color_format.hpp>
#include <sge/image/mizuiro_color_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace colored
{

typedef sge::image::mizuiro_color<
	sanguis::client::draw2d::sprite::colored::color_format
>::type color;

}
}
}
}
}

#endif
