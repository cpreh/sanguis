#include <sanguis/load/model/make_path.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/media_path.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::path
sanguis::load::model::make_path(
	fcppt::string const &_name
)
{
	boost::filesystem::path const path(
		sanguis::media_path()
		/
		FCPPT_TEXT("models")
		/
		_name
	);

	if(
		!boost::filesystem::exists(
			path
		)
	)
		throw
			sanguis::exception{
				FCPPT_TEXT("Model ")
				+
				_name
				+
				FCPPT_TEXT(" not found!")
			};

	return
		path;
}
