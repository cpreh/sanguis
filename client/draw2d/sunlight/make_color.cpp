#include "make_color.hpp"
#include "day_gradient.hpp"
#include "real.hpp"
#include "gradients.hpp"
#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/init.hpp>
#include <mizuiro/color/convert.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/math/twopi.hpp>

sge::image::color::any::object const
sanguis::client::draw2d::sunlight::make_color(
	real const sun_angle
)
{
	typedef sge::image::color::rgba32f dest_color;

	// TODO: we have to something sensible for the night as well!
	// Maybe add more stuff to the day gradient
	return
		sun_angle < 0.f
		?
			dest_color(
				sge::image::color::init::red %= 0.,
				sge::image::color::init::blue %= 0.2,
				sge::image::color::init::green %= 0.
			)
		:
			// convert into something that sge::image::color::any supports
			mizuiro::color::convert<
				dest_color::format
			>(
				day_gradient().interpolate(
					sun_angle
					/ fcppt::math::twopi<real>() // normalize it
				)
			);
}
