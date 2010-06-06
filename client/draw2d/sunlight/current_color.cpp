#include "current_color.hpp"
#include "current_intensity.hpp"
#include "make_color.hpp"
#include <fcppt/variant/object_impl.hpp>

sge::image::color::any::object const
sanguis::client::draw2d::sunlight::current_color()
{
	return
		sunlight::make_color(
			current_intensity()
		);
}
