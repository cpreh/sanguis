#ifndef SANGUIS_TOOLS_ANIMATIONS_QTUTIL_FROM_SGE_COLOR_FORMAT_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_QTUTIL_FROM_SGE_COLOR_FORMAT_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{
namespace qtutil
{

QImage::Format
from_sge_color_format(
	sge::image::color::format
);

}
}
}
}

#endif
