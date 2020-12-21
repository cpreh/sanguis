#include <sanguis/client/gui/style/text_color.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <fcppt/literal.hpp>


sge::image::color::any::object
sanguis::client::gui::style::text_color()
{
	using
	channel_type
	=
	sge::image::color::rgba8::format::channel_type;

	return
		sge::image::color::any::object{
			sge::image::color::rgba8(
				(sge::image::color::init::red() = fcppt::literal<channel_type>(0))
				(sge::image::color::init::green() = fcppt::literal<channel_type>(240)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				(sge::image::color::init::blue() = fcppt::literal<channel_type>(255)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				(sge::image::color::init::alpha() = fcppt::literal<channel_type>(255)) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			)
		};
}
