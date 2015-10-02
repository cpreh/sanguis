#include <sanguis/tiles/impl/load_file.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/load.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::image2d::optional_file_unique_ptr
sanguis::tiles::impl::load_file(
	sge::image2d::system &_system,
	boost::filesystem::path const &_path
)
{
	return
		boost::filesystem::exists(
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
