#ifndef SANGUIS_TOOLS_ANIMATIONS_FRAME_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_FRAME_HPP_INCLUDED

#include <sanguis/model/cell_area_fwd.hpp>
#include <sanguis/tools/animations/frame_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
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
		sge::image2d::view::const_object const &,
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
