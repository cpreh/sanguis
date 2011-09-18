#include <sanguis/client/config/settings/set_key.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/config/settings/get_or_create_section.hpp>
#include <sanguis/client/config/settings/get_or_create_entry.hpp>
#include <fcppt/text.hpp>

void
sanguis::client::config::settings::set_key(
	settings::object &_object,
	fcppt::string const &_section,
	fcppt::string const &_key,
	fcppt::string const &_value
)
{
	settings::get_or_create_entry(
		settings::get_or_create_section(
			_object.sections(),
			_section
		),
		_key,
		FCPPT_TEXT("")
	).value =
		_value;
}
