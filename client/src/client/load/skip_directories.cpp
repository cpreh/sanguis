#include <sanguis/client/load/skip_directories.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::directory_iterator
sanguis::client::load::skip_directories(
	boost::filesystem::directory_iterator _it
)
{
	while(
		_it != boost::filesystem::directory_iterator()
		&& boost::filesystem::is_directory(*_it)
	)
		++_it;

	return _it;
}
