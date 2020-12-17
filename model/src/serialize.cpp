#include <sanguis/model/exception.hpp>
#include <sanguis/model/object_fwd.hpp>
#include <sanguis/model/serialize.hpp>
#include <sanguis/model/impl/serialize/object.hpp>
#include <sge/parse/json/array_or_object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/output/to_file.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


void
sanguis::model::serialize(
	std::filesystem::path const &_path,
	sanguis::model::object const &_model
)
try
{
	if(
		!sge::parse::json::output::to_file(
			_path,
			sge::parse::json::start(
				sge::parse::json::array_or_object(
					sanguis::model::impl::serialize::object(
						_model
					)
				)
			)
		)
	)
	{
		throw
			sanguis::model::exception{
				FCPPT_TEXT("Failure")
			};
	}
}
catch(
	fcppt::exception const &_error
)
{
	throw
		sanguis::model::exception{
			fcppt::filesystem::path_to_string(
				_path
			)
			+
			FCPPT_TEXT(": ")
			+
			_error.string()
		};
}
