#ifndef SANGUIS_TOOLS_ANIMATIONS_MAKE_FRAMES_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_MAKE_FRAMES_HPP_INCLUDED

#include <sanguis/model/animation_fwd.hpp>
#include <sanguis/model/object_fwd.hpp>
#include <sanguis/tools/animations/frame_container.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <QWidget>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

sanguis::tools::animations::frame_container
make_frames(
	QImage const &,
	fcppt::reference<
		QWidget
	>,
	sanguis::model::object const &,
	sanguis::model::animation const &
);

}
}
}

#endif
