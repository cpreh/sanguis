#ifndef SANGUIS_TOOLS_ANIMATIONS_QT_STRING_TO_FCPPT_HPP_INCLUDED
#define SANGUIS_TOOLS_ANIMATIONS_QT_STRING_TO_FCPPT_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <QString>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace animations
{

fcppt::string
qt_string_to_fcppt(
	QString const &
);

}
}
}

#endif
