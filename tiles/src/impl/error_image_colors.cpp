#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/impl/error_image_color_pair.hpp>
#include <sanguis/tiles/impl/error_image_colors.hpp>
#include <sge/image/color/predef.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::tiles::impl::error_image_color_pair
sanguis::tiles::impl::error_image_colors(
	sanguis::tiles::error const _error
)
{
	switch(
		_error
	)
	{
	case sanguis::tiles::error::missing_foreground:
		return
			sanguis::tiles::impl::error_image_color_pair{
				sge::image::color::predef::black(),
				sge::image::color::predef::magenta()
			};
	case sanguis::tiles::error::missing_background:
		return
			sanguis::tiles::impl::error_image_color_pair{
				sge::image::color::predef::white(),
				sge::image::color::predef::green()
			};
	case sanguis::tiles::error::missing_object:
		return
			sanguis::tiles::impl::error_image_color_pair{
				sge::image::color::predef::white(),
				sge::image::color::predef::blue()
			};
	}

	FCPPT_ASSERT_UNREACHABLE;
}
