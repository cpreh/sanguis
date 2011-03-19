#include "get_or_default.hpp"
#include "get_or_create_section.hpp"
#include "get_or_create_entry.hpp"
#include "object.hpp"
#include <sge/parse/ini/entry.hpp>
#include <algorithm>

fcppt::string const
sanguis::client::config::settings::get_or_default(
	settings::object &_object,
	fcppt::string const &_section_name,
	fcppt::string const &_key,
	fcppt::string const &_default_value
)
{
	return 
		settings::get_or_create_entry(
			settings::get_or_create_section(
				_object.sections(),
				_section_name
			),
			_key,
			_default_value
		).value;
}
