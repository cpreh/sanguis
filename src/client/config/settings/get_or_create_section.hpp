#ifndef SANGUIS_CLIENT_CONFIG_SETTINGS_GET_OR_CREATE_SECTION_HPP_INCLUDED
#define SANGUIS_CLIENT_CONFIG_SETTINGS_GET_OR_CREATE_SECTION_HPP_INCLUDED

#include <sge/parse/ini/section_fwd.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace client
{
namespace config
{
namespace settings
{

sge::parse::ini::section &
get_or_create_section(
	sge::parse::ini::section_vector &sections_,
	fcppt::string const &section_name_
);

}
}
}
}

#endif
