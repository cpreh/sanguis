#include "current_color.hpp"
#include "current_sun_angle.hpp"
#include "make_color.hpp"
#include <fcppt/variant/object_impl.hpp>

sge::image::color::any::object const
sanguis::client::draw2d::sunlight::current_color()
{
	return
		sunlight::make_color(
			sunlight::current_sun_angle()
		);
}
