#include <sanguis/tiles/error.hpp>
#include <sanguis/tiles/impl/error_image_color_pair.hpp>
#include <sanguis/tiles/impl/error_image_colors.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <fcppt/enum/make_invalid.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sanguis::tiles::impl::error_image_color_pair
sanguis::tiles::impl::error_image_colors(sanguis::tiles::error const _error)
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_DISABLE_GCC_WARNING(-Wswitch-default)
  switch (_error)
  {
  case sanguis::tiles::error::missing_foreground:
    return sanguis::tiles::impl::error_image_color_pair{
        sge::image::color::any::object{sge::image::color::predef::black()},
        sge::image::color::any::object{sge::image::color::predef::magenta()}};
  case sanguis::tiles::error::missing_background:
    return sanguis::tiles::impl::error_image_color_pair{
        sge::image::color::any::object{sge::image::color::predef::white()},
        sge::image::color::any::object{sge::image::color::predef::green()}};
  case sanguis::tiles::error::missing_object:
    return sanguis::tiles::impl::error_image_color_pair{
        sge::image::color::any::object{sge::image::color::predef::white()},
        sge::image::color::any::object{sge::image::color::predef::blue()}};
  }
  FCPPT_PP_POP_WARNING

  throw fcppt::enum_::make_invalid(_error);
}
