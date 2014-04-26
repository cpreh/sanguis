#ifndef SANGUIS_TOOLS_ANIMATIONS_FRAME_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_FRAME_HPP_INCLUDED

#include <sanguis/model/cell_area_fwd.hpp>
#include <sanguis/tools/animations/frame_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <memory>
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
		QWidget &,
		QImage const &,
		sanguis::model::cell_area const &
	);

	frame(
		frame &&
	);

	frame &
	operator=(
		frame &&
	);

	~frame();

	QLabel &
	label();

	QPixmap const &
	pixmap() const;
private:
	typedef
	std::unique_ptr<
		QLabel
	>
	label_unique_ptr;

	QPixmap pixmap_;

	label_unique_ptr label_;
};

}
}
}

#endif
