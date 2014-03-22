#include <sanguis/model/cell_area.hpp>
#include <sanguis/tools/animations/frame.hpp>
#include <sanguis/tools/animations/qtutil/image_from_view.hpp>
#include <sge/image2d/rect.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/math/box/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::frame::frame(
	QWidget &_parent,
	sge::image2d::view::const_object const &_view,
	sanguis::model::cell_area const &_area
)
:
	pixmap_(
		QPixmap::fromImage(
			*sanguis::tools::animations::qtutil::image_from_view(
				sge::image2d::view::sub(
					_view,
					fcppt::math::box::structure_cast<
						sge::image2d::rect
					>(
						_area
					)
				)
			)
		)
	),
	label_(
		fcppt::make_unique_ptr<
			QLabel
		>(
			&_parent
		)
	)
{
	label_->setPixmap(
		pixmap_
	);

	label_->show();
}

sanguis::tools::animations::frame::frame(
	frame &&
) = default;

sanguis::tools::animations::frame &
sanguis::tools::animations::frame::operator=(
	frame &&
) = default;

sanguis::tools::animations::frame::~frame()
{
}

QLabel &
sanguis::tools::animations::frame::label()
{
	return
		*label_;
}
