#include <sanguis/load/next_file.hpp>
#include <sanguis/load/skip_directories.hpp>
#include <fcppt/filesystem/is_regular.hpp>


fcppt::filesystem::directory_iterator const
sanguis::load::next_file(
	fcppt::filesystem::directory_iterator _it
)
{
	if(
		_it != fcppt::filesystem::directory_iterator()
		&& fcppt::filesystem::is_regular(*_it)
	)
		++_it;

	return
		sanguis::load::skip_directories(
			_it
		);
}
