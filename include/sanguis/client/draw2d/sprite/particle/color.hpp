#ifndef SANGUIS_CLIENT_DRAW2D_SPRITE_PARTICLE_COLOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SPRITE_PARTICLE_COLOR_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/particle/color_format.hpp>
#include <sge/image/color/object.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sprite
{
namespace particle
{

typedef sge::image::color::object<
	color_format
>::type color;

}
}
}
}
}

#endif
