#include <sanguis/client/draw2d/sunlight/make_color.hpp>
#include <sanguis/client/draw2d/sunlight/day_gradient.hpp>
#include <sanguis/client/draw2d/sunlight/gradients.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/object.hpp>
#include <mizuiro/color/convert.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::image::color::any::object const
sanguis::client::draw2d::sunlight::make_color(
	real const _sun_angle
)
{
	return
		// convert into something that sge::image::color::any supports
		sge::image::color::any::object(
			mizuiro::color::convert<
				sge::image::color::rgba32f_format
			>(
				day_gradient().interpolate(
					_sun_angle
				)
			)
		);
}
