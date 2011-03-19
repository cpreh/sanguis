#include "make_color.hpp"
#include "day_gradient.hpp"
#include "gradients.hpp"
#include <sge/image/color/rgba32f_format.hpp>
#include <mizuiro/color/convert.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::image::color::any::object const
sanguis::client::draw2d::sunlight::make_color(
	real const _sun_angle
)
{
	return
		// convert into something that sge::image::color::any supports
		mizuiro::color::convert<
			sge::image::color::rgba32f_format
		>(
			day_gradient().interpolate(
				_sun_angle
			)
		);
}
