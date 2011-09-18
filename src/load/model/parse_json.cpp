#include <sanguis/load/model/parse_json.hpp>
#include <sanguis/load/log.hpp>
#include <sge/parse/json/parse_file.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>

void
sanguis::load::model::parse_json(
	fcppt::filesystem::path const &_path,
	sge::parse::json::object &_object_return
)
{
	fcppt::filesystem::path const file(
		_path
		/
		(
			fcppt::filesystem::stem(
				_path
			)
			+ FCPPT_TEXT(".json")
		)
	);


	if(
		!sge::parse::json::parse_file(
			file,
			_object_return
		)
	)
	{
		FCPPT_LOG_WARNING(
			sanguis::load::log(),
			fcppt::log::_
				<< file
				<< FCPPT_TEXT(" contains errors!")
			);
	}
}
