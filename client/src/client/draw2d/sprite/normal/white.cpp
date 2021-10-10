#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/client/draw2d/sprite/normal/color_format.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>

sanguis::client::draw2d::sprite::normal::color sanguis::client::draw2d::sprite::normal::white()
{
  return sge::image::color::convert<sanguis::client::draw2d::sprite::normal::color_format>(
      sge::image::color::predef::white());
}
