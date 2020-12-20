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
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/parameters_no_function.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::config::settings::object::object(
	fcppt::log::context_reference const _log_context,
	std::filesystem::path &&_path
)
:
	log_{
		_log_context,
		sanguis::client::config::log_location(),
		fcppt::log::parameters_no_function(
			fcppt::log::name{
				FCPPT_TEXT("settings")
			}
		)
	},
	path_{
		std::move(
			_path
		)
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
					// TODO(philipp): either::from?
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

FCPPT_PP_POP_WARNING

sanguis::client::config::settings::object::~object()
= default;

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
