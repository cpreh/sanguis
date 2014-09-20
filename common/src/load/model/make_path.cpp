#include <sanguis/exception.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/load/model/make_path.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::path
sanguis::load::model::make_path(
	sanguis::load::model::path const &_path
)
{
	boost::filesystem::path const path(
		sanguis::media_path()
		/
		FCPPT_TEXT("models")
		/
		_path.get()
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
				fcppt::filesystem::path_to_string(
					_path.get()
				)
				+
				FCPPT_TEXT(" not found!")
			};

	return
		path;
}
