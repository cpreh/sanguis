#include <sanguis/client/load/first_file.hpp>
#include <sanguis/client/load/skip_directories.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::directory_iterator
sanguis::client::load::first_file(
	boost::filesystem::path const &_path
)
{
	return
		sanguis::client::load::skip_directories(
			boost::filesystem::directory_iterator(
				_path
			)
		);
}
