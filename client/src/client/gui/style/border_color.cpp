#include <sanguis/client/gui/style/border_color.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>


sge::image::color::any::object
sanguis::client::gui::style::border_color()
{
	return
		sge::image::color::predef::magenta();
}
