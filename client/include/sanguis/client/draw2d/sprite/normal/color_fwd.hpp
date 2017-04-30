#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_COLOR_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_NORMAL_COLOR_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/normal/color_format.hpp>
#include <sge/image/pixel/mizuiro_type_fwd.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace normal
{

typedef
sge::image::pixel::mizuiro_type<
	sanguis::client::draw2d::sprite::normal::color_format
>
color;

}
}
}
}
}

#endif
