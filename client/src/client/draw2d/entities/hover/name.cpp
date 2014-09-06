#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/string.hpp>


sanguis::client::draw2d::entities::hover::name::name(
	fcppt::string const &_text,
	sge::image::color::any::object const &_color
)
:
	text_{
		_text
	},
	color_{
		_color
	}
{
}

fcppt::string const &
sanguis::client::draw2d::entities::hover::name::text() const
{
	return
		text_;
}

sge::image::color::any::object const &
sanguis::client::draw2d::entities::hover::name::color() const
{
	return
		color_;
}
