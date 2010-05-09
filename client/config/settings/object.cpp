#include "object.hpp"
#include <sge/parse/ini/parse_file.hpp>
#include <sge/parse/exception.hpp>

sanguis::client::config::settings::object::object(
	fcppt::filesystem::path const &path_
)
try
:
	path_(path_)
{
	if(
		!sge::parse::ini::parse_file(
			path_,
			sections_
		)
	)
		sections_.clear();

}
catch(
	sge::parse::exception const &
)
{
}

sanguis::client::config::settings::object::~object()
{
}

sge::parse::ini::section_vector &
sanguis::client::config::settings::object::sections()
{
	return sections_;
}

sge::parse::ini::section_vector const &
sanguis::client::config::settings::object::sections() const
{
	return sections_;
}

void
sanguis::client::config::settings::object::save()
{
	// TODO!
}
