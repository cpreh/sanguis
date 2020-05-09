#include <sanguis/tiles/impl/load_file.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/load.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


sge::image2d::optional_file_unique_ptr
sanguis::tiles::impl::load_file(
	sge::image2d::system_ref const _system,
	std::filesystem::path const &_path
)
{
	return
		std::filesystem::exists(
			_path
		)
		?
			sge::image2d::load(
				_system,
				_path
			)
		:
			sge::image2d::optional_file_unique_ptr()
		;
}
