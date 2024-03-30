#include <sanguis/enemy_kind.hpp>
#include <sanguis/client/draw2d/entities/enemy_color.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::image::color::any::object
sanguis::client::draw2d::entities::enemy_color(sanguis::enemy_kind const _kind)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_kind)
  {
  case sanguis::enemy_kind::normal:
    return sge::image::color::any::object{sge::image::color::predef::white()};
  case sanguis::enemy_kind::champion:
    return sge::image::color::any::object{sge::image::color::rgba8(
        (sge::image::color::init::red() %=
         0.5) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        (sge::image::color::init::green() %=
         0.5) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        (sge::image::color::init::blue() %= 1.)(sge::image::color::init::alpha() %= 1.))};
  case sanguis::enemy_kind::unique:
    return sge::image::color::any::object{sge::image::color::predef::gold()};
  case sanguis::enemy_kind::boss:
    return sge::image::color::any::object{sge::image::color::predef::red()};
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_kind);
}
