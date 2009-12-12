#ifndef SANGUIS_DRAW_SPRITE_COLORED_COLOR_HPP_INCLUDED
#define SANGUIS_DRAW_SPRITE_COLORED_COLOR_HPP_INCLUDED

#include "color_format.hpp"
#include <sge/image/color/object.hpp>

namespace sanguis
{
namespace draw
{
namespace sprite
{
namespace colored
{

typedef sge::image::color::object<
	color_format
>::type color;

}
}
}
}

#endif
