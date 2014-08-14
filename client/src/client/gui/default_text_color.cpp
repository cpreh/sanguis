#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sge/image/color/predef.hpp>


sanguis::gui::text_color
sanguis::client::gui::default_text_color()
{
	return
		sanguis::gui::text_color{
			sge::image::color::predef::black()
		};
}
