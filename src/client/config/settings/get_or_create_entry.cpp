#include "get_or_create_entry.hpp"
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <algorithm>

sge::parse::ini::entry &
sanguis::client::config::settings::get_or_create_entry(
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


