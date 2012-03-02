#include <sanguis/load/first_file.hpp>
#include <sanguis/load/skip_directories.hpp>
#include <fcppt/filesystem/directory_iterator.hpp>


fcppt::filesystem::directory_iterator const
sanguis::load::first_file(
	fcppt::filesystem::path const &_path
)
{
	return
		sanguis::load::skip_directories(
			fcppt::filesystem::directory_iterator(
				_path
			)
		);
}
