#include <sanguis/tools/animations/qtutil/from_sge_color_format.hpp>
#include <sanguis/tools/animations/qtutil/image_from_view.hpp>
#include <sanguis/tools/animations/qtutil/image_unique_ptr.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/data.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/pitch.hpp>
#include <sge/image2d/view/size.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::qtutil::image_unique_ptr
sanguis::tools::animations::qtutil::image_from_view(
	sge::image2d::view::const_object const &_view
)
{
	sge::image2d::dim const size(
		sge::image2d::view::size(
			_view
		)
	);

	sge::image::color::format const format(
		sge::image2d::view::format(
			_view
		)
	);

	return
		fcppt::make_unique_ptr<
			QImage
		>(
			sge::image2d::view::data(
				_view
			),
			fcppt::cast::size<
				int
			>(
				fcppt::cast::to_signed(
					size.w()
				)
			),
			fcppt::cast::size<
				int
			>(
				fcppt::cast::to_signed(
					size.h()
				)
			),
			fcppt::cast::size<
				int
			>(
				fcppt::cast::to_signed(
					size.w()
					*
					sge::image::color::format_stride(
						format
					)
				)
				+
				sge::image2d::view::pitch(
					_view
				).w()
			),
			sanguis::tools::animations::qtutil::from_sge_color_format(
				format
			)
		);
}
