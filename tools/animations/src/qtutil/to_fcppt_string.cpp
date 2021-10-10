#include <sanguis/tools/animations/qtutil/to_fcppt_string.hpp>
#include <fcppt/public_config.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QString>
#include <fcppt/config/external_end.hpp>

fcppt::string sanguis::tools::animations::qtutil::to_fcppt_string(QString const &_string)
{
  return
#if defined(FCPPT_NARROW_STRING)
      _string.toStdString();
#else
      _string.toStdWString();
#endif
}
