#include "get_or_create_section.hpp"
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/header_name_equal.hpp>
#include <algorithm>

sge::parse::ini::section &
sanguis::client::config::settings::get_or_create_section(
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
