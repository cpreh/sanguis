#ifndef SANGUIS_TOOLS_ANIMATIONS_QTUTIL_FROM_FCPPT_STRING_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_QTUTIL_FROM_FCPPT_STRING_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QString>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tools::animations::qtutil
{

QString from_fcppt_string(fcppt::string const &);

}

#endif
