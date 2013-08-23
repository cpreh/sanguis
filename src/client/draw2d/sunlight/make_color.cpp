#include <sanguis/client/draw2d/sunlight/day_gradient.hpp>
#include <sanguis/client/draw2d/sunlight/gradients.hpp>
#include <sanguis/client/draw2d/sunlight/make_color.hpp>
#include <sanguis/client/draw2d/sunlight/real.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/object.hpp>


sge::image::color::any::object const
sanguis::client::draw2d::sunlight::make_color(
	sanguis::client::draw2d::sunlight::real const _sun_angle
)
{
	return
		// convert into something that sge::image::color::any supports
		sge::image::color::any::object(
			sge::image::color::convert<
				sge::image::color::rgba32f_format
			>(
				day_gradient().interpolate(
					_sun_angle
				)
			)
		);
}
