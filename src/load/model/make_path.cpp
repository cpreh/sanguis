#include <sanguis/load/model/make_path.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/media_path.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/text.hpp>

fcppt::filesystem::path const
sanguis::load::model::make_path(
	fcppt::string const &_name
)
{
	fcppt::filesystem::path const path(
		sanguis::media_path()
		/
		_name
	);

	if(
		!fcppt::filesystem::exists(
			path
		)
	)
		throw sanguis::exception(
			FCPPT_TEXT("Model ")
			+ _name
			+ FCPPT_TEXT(" not found!")
		);

	return path;
}
