#include <sanguis/tools/animations/qtutil/from_fcppt_string.hpp>
#include <fcppt/public_config.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QString>
#include <fcppt/config/external_end.hpp>

QString sanguis::tools::animations::qtutil::from_fcppt_string(fcppt::string const &_string)
{
  return
#if defined(FCPPT_NARROW_STRING)
      QString::fromStdString(_string);
#else
      QString::fromStdWString(_string);
#endif
}
