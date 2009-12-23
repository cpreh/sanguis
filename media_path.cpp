#include "media_path.hpp"
#include <fcppt/filesystem/path.hpp>
#include <sge/config/find_path.hpp>
#include <sge/config/make_files.hpp>
#include <sge/text.hpp>
#include <boost/assign/list_of.hpp>

fcppt::filesystem::path const
sanguis::media_path()
{
	static fcppt::filesystem::path const ret(
		sge::config::find_path(
			sge::config::make_files(
				SGE_TEXT("sanguis")
			),
			SGE_TEXT("sanguis_media"),
			boost::assign::list_of(
				SGE_TEXT("media")
			)
		)
	);

	return ret; 
}
