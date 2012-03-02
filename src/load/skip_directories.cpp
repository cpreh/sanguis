#include <sanguis/load/skip_directories.hpp>
#include <fcppt/filesystem/is_directory.hpp>


fcppt::filesystem::directory_iterator const
sanguis::load::skip_directories(
	fcppt::filesystem::directory_iterator _it
)
{
	while(
		_it != fcppt::filesystem::directory_iterator()
		&& fcppt::filesystem::is_directory(*_it)
	)
		++_it;

	return _it;
}
