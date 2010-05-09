#ifndef SANGUIS_CONFIG_SETTINGS_GET_OR_CREATE_ENTRY_HPP_INCLUDED
#define SANGUIS_CONFIG_SETTINGS_GET_OR_CREATE_ENTRY_HPP_INCLUDED

#include <sge/parse/ini/section_fwd.hpp>
#include <sge/parse/ini/entry_fwd.hpp>
#include <fcppt/string.hpp>

namespace sanguis
{
namespace client
{
namespace config
{
namespace settings
{

sge::parse::ini::entry &
get_or_create_entry(
	sge::parse::ini::section &section_,
	fcppt::string const &key_,
	fcppt::string const &default_value_
);

}
}
}
}

#endif
