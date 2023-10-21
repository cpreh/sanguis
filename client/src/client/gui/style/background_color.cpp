#include <sanguis/client/gui/style/background_color.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>

sge::image::color::any::object sanguis::client::gui::style::background_color()
{
  return sge::image::color::any::object{sge::image::color::rgba8(
      (sge::image::color::init::red() %=
       0.18) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      (sge::image::color::init::green() %=
       0.18) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      (sge::image::color::init::blue() %=
       0.18) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      (sge::image::color::init::alpha() %=
       1.0) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      )};
}
