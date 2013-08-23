#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_MAKE_COLOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_MAKE_COLOR_HPP_INCLUDED

#include <sanguis/client/draw2d/sunlight/real.hpp>
#include <sge/image/color/any/object.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sunlight
{

sge::image::color::any::object const
make_color(
	sanguis::client::draw2d::sunlight::real sun_angle
);

}
}
}
}

#endif
