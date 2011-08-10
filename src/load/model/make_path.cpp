#include "make_path.hpp"
#include "../../exception.hpp"
#include "../../media_path.hpp"
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/text.hpp>

fcppt::filesystem::path const
sanguis::load::model::make_path(
	fcppt::string const &name
)
{
	fcppt::filesystem::path const path(
		media_path() / name
	);

	if(
		!fcppt::filesystem::exists(
			path
		)
	)
		throw exception(
			FCPPT_TEXT("Model ")
			+ name
			+ FCPPT_TEXT(" not found!")
		);

	return path;
}
