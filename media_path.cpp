#include "media_path.hpp"
#include <fcppt/filesystem/path.hpp>
#include <sge/config/find_path.hpp>
#include <sge/config/make_files.hpp>
#include <fcppt/text.hpp>
#include <boost/assign/list_of.hpp>

fcppt::filesystem::path const
sanguis::media_path()
{
	static fcppt::filesystem::path const ret(
		sge::config::find_path(
			sge::config::make_files(
				FCPPT_TEXT("sanguis")
			),
			FCPPT_TEXT("sanguis_media"),
			boost::assign::list_of(
				FCPPT_TEXT("media")
			)
		)
	);

	return ret; 
}
