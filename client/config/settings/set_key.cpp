#include "set_key.hpp"
#include "object.hpp"
#include "get_or_create_section.hpp"
#include "get_or_create_entry.hpp"
#include <fcppt/text.hpp>

void
sanguis::client::config::settings::set_key(
	object &object_,
	fcppt::string const &section_,
	fcppt::string const &key_,
	fcppt::string const &value_
)
{
	get_or_create_entry(
		get_or_create_section(
			object_.sections(),
			section_
		),
		key_,
		FCPPT_TEXT("")
	).value = value_;
}
