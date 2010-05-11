#include "media_path.hpp"
#include "exception.hpp"
#include <fcppt/filesystem/path.hpp>
#include <sge/config/find_path.hpp>
#include <sge/config/make_files.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/assign/list_of.hpp>

namespace
{

fcppt::filesystem::path const
find_path()
{
	sge::config::optional_path const path_(
		sge::config::find_path(
			sge::config::make_files(
				FCPPT_TEXT("sanguis")
			),
			FCPPT_TEXT("sanguis_media"),
			boost::assign::list_of(
				FCPPT_TEXT("media")
			)
			(
				MEDIA_PATH
			)
		)
	);

	if(
		!path_
	)
		throw sanguis::exception(
			FCPPT_TEXT("media path not found!")
		);
	
	return *path_;
}

}

fcppt::filesystem::path const
sanguis::media_path()
{
	static fcppt::filesystem::path const ret(
		find_path()
	);

	return ret; 
}
