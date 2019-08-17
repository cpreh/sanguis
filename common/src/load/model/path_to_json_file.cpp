#include <sanguis/load/model/path_to_json_file.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


std::filesystem::path
sanguis::load::model::path_to_json_file(
	std::filesystem::path const _path
)
{
	return
		_path
		/
		(
			fcppt::filesystem::stem(
				_path
			)
			+
			FCPPT_TEXT(".json")
		);
}
