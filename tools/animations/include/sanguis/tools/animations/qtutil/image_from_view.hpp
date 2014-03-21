#ifndef SANGUIS_TOOLS_ANIMATIONS_QTUTIL_IMAGE_FROM_VIEW_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_QTUTIL_IMAGE_FROM_VIEW_HPP_INCLUDED

#include <sanguis/tools/animations/qtutil/image_unique_ptr.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{
namespace qtutil
{

sanguis::tools::animations::qtutil::image_unique_ptr
image_from_view(
	sge::image2d::view::const_object const &
);

}
}
}
}

#endif
