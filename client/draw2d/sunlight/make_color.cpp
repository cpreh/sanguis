#include "make_color.hpp"
#include <sge/image/color/init.hpp>
#include <sge/image/color/rgb8.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::image::color::any::object const
sanguis::client::draw2d::sunlight::make_color(
	real const intensity
)
{
	// TODO: calculate a proper gradient!
	return
		sge::image::color::rgb8(
			sge::image::color::init::red %= intensity,
			sge::image::color::init::green %= intensity,
			sge::image::color::init::blue %= 0.2
		);
}
