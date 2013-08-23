#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_RGB32F_FORMAT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_RGB32F_FORMAT_HPP_INCLUDED

#include <sanguis/client/draw2d/sunlight/real.hpp>
#include <mizuiro/color/homogenous_static.hpp>
#include <mizuiro/color/layout/rgb.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sunlight
{

typedef mizuiro::color::homogenous_static<
	sanguis::client::draw2d::sunlight::real,
	mizuiro::color::layout::rgb
> rgb32f_format;

}
}
}
}

#endif
