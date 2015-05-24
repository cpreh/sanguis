#include <sanguis/model/cell_area.hpp>
#include <sanguis/tools/animations/frame.hpp>
#include <sanguis/tools/animations/qtutil/sub_image.hpp>
#include <sanguis/tools/animations/qtutil/to_rect.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QFrame>
#include <QImage>
#include <QLabel>
#include <QLayout>
#include <QPixmap>
#include <QRect>
#include <QWidget>
#include <fcppt/config/external_end.hpp>


sanguis::tools::animations::frame::frame(
	QWidget &_parent,
	QImage const &_image,
	sanguis::model::cell_area const &_area
)
:
	pixmap_(
		QPixmap::fromImage(
			sanguis::tools::animations::qtutil::sub_image(
				_image,
				sanguis::tools::animations::qtutil::to_rect(
					_area
				)
			)
		)
	),
	label_(
		fcppt::make_unique_ptr_fcppt<
			QLabel
		>(
			&_parent
		)
	)
{
	_parent.layout()->addWidget(
		label_.get_pointer()
	);

	label_->setFrameShape(
		QFrame::StyledPanel
	);

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

QPixmap const &
sanguis::tools::animations::frame::pixmap() const
{
	return
		pixmap_;
}
