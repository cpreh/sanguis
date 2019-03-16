#include <sanguis/log_parameters.hpp>
#include <sanguis/client/config/log_location.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sge/parse/ini/parse_file.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/parse/ini/start.hpp>
#include <sge/parse/ini/output/to_file.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
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
	path_{
		_path
	},
	start_{
		[
			this
		]{
			FCPPT_LOG_DEBUG(
				this->log_,
				fcppt::log::out
					<<
					FCPPT_TEXT("Trying to load settings from ")
					<<
					fcppt::filesystem::path_to_string(
						this->path_
					)
			)

			return
				fcppt::either::match(
					sge::parse::ini::parse_file(
						this->path_
					),
					[
						this
					](
						fcppt::optional::object<
							fcppt::parse::error<
								char
							>
						> const &_error
					)
					{
						fcppt::optional::maybe_void(
							_error,
							[
								this
							](
								fcppt::parse::error<
									char
								> const &_parse_error
							)
							{
								FCPPT_LOG_INFO(
									this->log_,
									fcppt::log::out
										<<
										FCPPT_TEXT("Loading the settings failed!")
										<<
										fcppt::from_std_string(
											_parse_error.get()
										)
								)
							}
						);

						return
							sge::parse::ini::start{
								sge::parse::ini::section_vector{}
							};
					},
					// TODO: either::from?
					[](
						sge::parse::ini::start &&_start
					)
					->
					sge::parse::ini::start
					{
						return
							std::move(
								_start
							);
					}
				);
		}()
	}
{
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
		fcppt::log::out
			<< FCPPT_TEXT("Trying to save settings to ")
			<< fcppt::filesystem::path_to_string(
				path_
			)
	)

	if(
		!sge::parse::ini::output::to_file(
			path_,
			start_
		)
	)
	{
		FCPPT_LOG_ERROR(
			log_,
			fcppt::log::out
				<< FCPPT_TEXT("Writing the settings failed!")
		)
	}
}

fcppt::log::object &
sanguis::client::config::settings::object::log() const
{
	return
		log_;
}
