#include "get_or_create_section.hpp"
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/header_name_equal.hpp>
#include <algorithm>

sge::parse::ini::section &
sanguis::client::config::settings::get_or_create_section(
	sge::parse::ini::section_vector &_sections,
	fcppt::string const &_section_name
)
{
	sge::parse::ini::section_vector::iterator it(
		std::find_if(
			_sections.begin(),
			_sections.end(),
			sge::parse::ini::header_name_equal(
				_section_name
			)
		)
	);

	if(
		it == _sections.end()
	)
		it =
			_sections.insert(
				_sections.end(),
				sge::parse::ini::section(
					_section_name
				)
			);

	return *it;
}
