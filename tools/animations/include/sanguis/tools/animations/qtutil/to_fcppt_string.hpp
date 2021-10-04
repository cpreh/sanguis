#ifndef SANGUIS_TOOLS_ANIMATIONS_QTUTIL_TO_FCPPT_STRING_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_QTUTIL_TO_FCPPT_STRING_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QString>
#include <fcppt/config/external_end.hpp>


namespace sanguis::tools::animations::qtutil
{

fcppt::string
to_fcppt_string(
	QString const &
);

}

#endif
