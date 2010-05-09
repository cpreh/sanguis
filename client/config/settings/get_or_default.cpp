#include "get_or_default.hpp"
#include "object.hpp"
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/header_name_equal.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <algorithm>

namespace
{

sge::parse::ini::section &
get_or_create_section(
	sge::parse::ini::section_vector &sections_,
	fcppt::string const &section_name_
)
{
	sge::parse::ini::section_vector::iterator it(
		std::find_if(
			sections_.begin(),
			sections_.end(),
			sge::parse::ini::header_name_equal(
				section_name_
			)
		)
	);

	if(
		it == sections_.end()
	)
		it =
			sections_.insert(
				sections_.end(),
				sge::parse::ini::section(
					section_name_
				)
			);
	
	return *it;
}

sge::parse::ini::entry &
get_or_create_entry(
	sge::parse::ini::section &section_,
	fcppt::string const &key_,
	fcppt::string const &default_value_
)
{
	sge::parse::ini::entry_vector &entries_(
		section_.entries
	);

	sge::parse::ini::entry_vector::iterator it(
		std::find_if(
			entries_.begin(),
			entries_.end(),
			sge::parse::ini::entry_name_equal(
				key_
			)
		)
	);

	if(
		it == entries_.end()
	)
		it =
			entries_.insert(
				entries_.end(),
				sge::parse::ini::entry(
					key_,
					default_value_
				)
			);
	
	return *it;
}

}

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
