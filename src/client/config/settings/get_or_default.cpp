#include "get_or_default.hpp"
#include "get_or_create_section.hpp"
#include "get_or_create_entry.hpp"
#include "object.hpp"
#include <sge/parse/ini/entry.hpp>
#include <algorithm>

fcppt::string const
sanguis::client::config::settings::get_or_default(
	object &object_,
	fcppt::string const &section_name_,
	fcppt::string const &key_,
	fcppt::string const &default_value_
)
{
	return 
		get_or_create_entry(
			get_or_create_section(
				object_.sections(),
				section_name_
			),
			key_,
			default_value_
		).value;
}
