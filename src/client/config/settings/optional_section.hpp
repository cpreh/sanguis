#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_OPTIONAL_SECTION_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_OPTIONAL_SECTION_HPP_INCLUDED

#include <fcppt/optional_fwd.hpp>
#include <sge/parse/ini/section_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace config
{
namespace settings
{

typedef fcppt::optional<
	sge::parse::ini::section
> optional_section;

}
}
}
}

#endif
