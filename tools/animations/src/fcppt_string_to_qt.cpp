#include <sanguis/tools/animations/fcppt_string_to_qt.hpp>
#include <fcppt/public_config.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QString>
#include <fcppt/config/external_end.hpp>


QString
sanguis::tools::animations::fcppt_string_to_qt(
	fcppt::string const &_string
)
{
	return
#if defined(FCPPT_NARROW_STRING)
		QString::fromStdString(
			_string
		);
#else
		QString::fromStdWString(
			_string
		);
#endif
}
