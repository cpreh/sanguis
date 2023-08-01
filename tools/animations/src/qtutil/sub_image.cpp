#include <sanguis/tools/animations/qtutil/sub_image.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QImage>
#include <QRect>
#include <limits>
#include <fcppt/config/external_end.hpp>

QImage sanguis::tools::animations::qtutil::sub_image(QImage const &_image, QRect const _rect)
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

  return QImage(
      _image.bits() + // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
          _rect.x() * _image.depth() /
              std::numeric_limits<unsigned char>::
                  digits + // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
          _rect.y() * _image.bytesPerLine(),
      _rect.width(),
      _rect.height(),
      _image.bytesPerLine(),
      _image.format());

FCPPT_PP_POP_WARNING
}
