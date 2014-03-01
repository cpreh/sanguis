#include <sanguis/model/deserialize.hpp>
#include <sanguis/model/exception.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/aux_/deserialize/object.hpp>
#include <sge/parse/json/parse_file_exn.hpp>
#include <sge/parse/json/start.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::model::object
sanguis::model::deserialize(
	boost::filesystem::path const &_path
)
try
{
	return
		sanguis::model::aux_::deserialize::object(
			sge::parse::json::parse_file_exn(
				_path
			).object()
		);
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
