#ifndef SANGUIS_TOOLS_ANIMATIONS_FRAME_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_FRAME_HPP_INCLUDED

#include <sanguis/model/cell_area_fwd.hpp>
#include <sanguis/tools/animations/frame_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

class frame
{
	FCPPT_NONCOPYABLE(
		frame
	);
public:
	frame(
		fcppt::reference<
			QWidget
		>,
		QImage const &,
		sanguis::model::cell_area const &
	);

	frame(
		frame &&
	)
	noexcept;

	frame &
	operator=(
		frame &&
	)
	noexcept;

	~frame();

	[[nodiscard]]
	QLabel &
	label();

	[[nodiscard]]
	QPixmap const &
	pixmap() const;
private:
	using
	label_unique_ptr
	=
	fcppt::unique_ptr<
		QLabel
	>;

	QPixmap pixmap_;

	label_unique_ptr label_;
};

}
}
}

#endif
