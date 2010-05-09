#include "object.hpp"
#include "../../../exception.hpp"
#include <sge/parse/ini/output/to_file.hpp>
#include <sge/parse/ini/parse_file.hpp>
#include <sge/parse/exception.hpp>
#include <fcppt/text.hpp>

sanguis::client::config::settings::object::object(
	fcppt::filesystem::path const &path_
)
:
	path_(path_)
{
	try
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
	if(
		!sge::parse::ini::output::to_file(
			path_,
			sections_
		)
	)
		throw exception(
			FCPPT_TEXT("Writing the settings failed!")
		);
}
