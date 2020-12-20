#include <sanguis/client/draw2d/entities/hover/name.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::hover::name::name(
	fcppt::string &&_text,
	sge::image::color::any::object _color
)
:
	text_{
		std::move(
			_text
		)
	},
	color_{
		std::move(
			_color
		)
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
