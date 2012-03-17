#include <sanguis/load/next_file.hpp>
#include <sanguis/load/skip_directories.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::directory_iterator const
sanguis::load::next_file(
	boost::filesystem::directory_iterator _it
)
{
	if(
		_it != boost::filesystem::directory_iterator()
		&& boost::filesystem::is_regular_file(*_it)
	)
		++_it;

	return
		sanguis::load::skip_directories(
			_it
		);
}
