#include <sanguis/tools/animations/exception.hpp>
#include <sanguis/tools/animations/qtutil/from_sge_color_format.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_to_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <fcppt/config/external_end.hpp>


QImage::Format
sanguis::tools::animations::qtutil::from_sge_color_format(
	sge::image::color::format const _format
)
{
	// TODO: Which ones should we use here?
	switch(
		_format
	)
	{
	case sge::image::color::format::bgr8:
		return
			QImage::Format_RGB888;
	case sge::image::color::format::bgra8:
		return
			QImage::Format_ARGB32;
	case sge::image::color::format::bgrx8:
		return
			QImage::Format_RGB32;
	case sge::image::color::format::a8:
	case sge::image::color::format::l8:
	case sge::image::color::format::r32f:
	case sge::image::color::format::la8:
	case sge::image::color::format::rgb8:
	case sge::image::color::format::rgba8:
	case sge::image::color::format::rgbx8:
	case sge::image::color::format::rgb32f:
	case sge::image::color::format::bgr32f:
	case sge::image::color::format::rgba32f:
	case sge::image::color::format::bgra32f:
	case sge::image::color::format::srgb8:
	case sge::image::color::format::srgba8:
		throw
			sanguis::tools::animations::exception{
				FCPPT_TEXT("Unsupported format ")
				+
				sge::image::color::format_to_string(
					_format
				)
			};
	}

	FCPPT_ASSERT_UNREACHABLE;
}
