#include <sanguis/client/draw2d/font_color_format.hpp>
#include <sge/font/draw/color_format.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>

sge::image::color::format sanguis::client::draw2d::font_color_format()
{
  return sge::font::draw::color_format(sge::image::color::optional_format());
}
