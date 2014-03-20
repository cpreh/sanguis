#include <sanguis/model/exception.hpp>
#include <sanguis/model/object_fwd.hpp>
#include <sanguis/model/serialize.hpp>
#include <sanguis/model/aux_/serialize/object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/output/to_file.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


void
sanguis::model::serialize(
	boost::filesystem::path const &_path,
	sanguis::model::object const &_model
)
try
{
	sge::parse::json::output::to_file(
		_path,
		sge::parse::json::start(
			sanguis::model::aux_::serialize::object(
				_model
			)
		)
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
