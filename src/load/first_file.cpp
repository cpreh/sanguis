#include <sanguis/load/first_file.hpp>
#include <sanguis/load/skip_directories.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::directory_iterator const
sanguis::load::first_file(
	boost::filesystem::path const &_path
)
{
	return
		sanguis::load::skip_directories(
			boost::filesystem::directory_iterator(
				_path
			)
		);
}
