#include <sanguis/load/model/parse_json.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/filesystem/stem.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::parse::json::start
sanguis::load::model::parse_json(
	boost::filesystem::path const &_path
)
{
	return
		sge::parse::json::parse_file_exn(
			_path
			/
			(
				fcppt::filesystem::stem(
					_path
				)
				+ FCPPT_TEXT(".json")
			)
		);
}
