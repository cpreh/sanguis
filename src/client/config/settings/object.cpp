#include "object.hpp"
#include "../../log.hpp"
#include "../../../exception.hpp"
#include <sge/parse/ini/output/to_file.hpp>
#include <sge/parse/ini/parse_file.hpp>
#include <sge/parse/exception.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/text.hpp>

sanguis::client::config::settings::object::object(
	fcppt::filesystem::path const &_path
)
:
	path_(_path)
{
	FCPPT_LOG_DEBUG(
		client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Trying to load settings from ")
			<< fcppt::filesystem::path_to_string(
				_path
			)
	);

	try
	{
		if(
			!sge::parse::ini::parse_file(
				path_,
				sections_
			)
		)
		{
			sections_.clear();

			FCPPT_LOG_INFO(
				client::log(),
				fcppt::log::_
					<< FCPPT_TEXT("Loading the settings failed!")
			);
		}
	}
	catch(
		sge::parse::exception const &_error
	)
	{
		FCPPT_LOG_INFO(
			client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Loading the settings failed with: ")
				<< _error.string()
		);
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
sanguis::client::config::settings::object::save() const
{
	FCPPT_LOG_DEBUG(
		client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Trying to save settings to ")
			<< fcppt::filesystem::path_to_string(
				path_
			)
	);

	if(
		!sge::parse::ini::output::to_file(
			path_,
			sections_
		)
	)
	{
		FCPPT_LOG_ERROR(
			client::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Writing the settings failed!")
		);
	}
}
