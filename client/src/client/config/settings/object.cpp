#include <sanguis/exception.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/client/config/log_location.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sge/parse/exception.hpp>
#include <sge/parse/result.hpp>
#include <sge/parse/result_code.hpp>
#include <sge/parse/ini/parse_file.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/output/to_file.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::client::config::settings::object::object(
	fcppt::log::context &_log_context,
	boost::filesystem::path const &_path
)
:
	log_{
		_log_context,
		sanguis::client::config::log_location(),
		sanguis::log_parameters(
			fcppt::log::name{
				FCPPT_TEXT("settings")
			}
		)
	},
	path_(
		_path
	),
	start_()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("Trying to load settings from ")
			<< fcppt::filesystem::path_to_string(
				_path
			)
	);

	try
	{
		// TODO: Direct initialization
		if(
			sge::parse::ini::parse_file(
				path_,
				start_
			).result_code()
			!=
			sge::parse::result_code::ok
		)
		{
			start_.sections.clear();

			FCPPT_LOG_INFO(
				log_,
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
			log_,
			fcppt::log::_
				<< FCPPT_TEXT("Loading the settings failed with: ")
				<< _error.string()
		);
	}
}

sanguis::client::config::settings::object::~object()
{
}

sge::parse::ini::start &
sanguis::client::config::settings::object::sections()
{
	return
		start_;
}

sge::parse::ini::start const &
sanguis::client::config::settings::object::sections() const
{
	return
		start_;
}

void
sanguis::client::config::settings::object::save() const
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("Trying to save settings to ")
			<< fcppt::filesystem::path_to_string(
				path_
			)
	);

	if(
		!sge::parse::ini::output::to_file(
			path_,
			start_
		)
	)
	{
		FCPPT_LOG_ERROR(
			log_,
			fcppt::log::_
				<< FCPPT_TEXT("Writing the settings failed!")
		);
	}
}

fcppt::log::object &
sanguis::client::config::settings::object::log() const
{
	return
		log_;
}
