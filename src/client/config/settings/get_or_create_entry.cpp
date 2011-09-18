#include <sanguis/client/config/settings/get_or_create_entry.hpp>
#include <sge/parse/ini/entry_vector.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

sge::parse::ini::entry &
sanguis::client::config::settings::get_or_create_entry(
	sge::parse::ini::section &_section,
	fcppt::string const &_key,
	fcppt::string const &_default_value
)
{
	sge::parse::ini::entry_vector &entries(
		_section.entries
	);

	sge::parse::ini::entry_vector::iterator it(
		std::find_if(
			entries.begin(),
			entries.end(),
			sge::parse::ini::entry_name_equal(
				_key
			)
		)
	);

	if(
		it == entries.end()
	)
		it =
			entries.insert(
				entries.end(),
				sge::parse::ini::entry(
					_key,
					_default_value
				)
			);

	return *it;
}
