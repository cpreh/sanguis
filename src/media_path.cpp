#include <sanguis/media_path.hpp>
#include <sanguis/build/media_path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::path const
sanguis::media_path()
{
	return
		sanguis::build_media_path();
}
