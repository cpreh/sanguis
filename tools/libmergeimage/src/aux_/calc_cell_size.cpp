#include <sanguis/tools/libmergeimage/exception.hpp>
#include <sanguis/tools/libmergeimage/aux_/calc_cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector_vector.hpp>
#include <sge/image/exception.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::aux_::cell_size const
sanguis::tools::libmergeimage::aux_::calc_cell_size(
	sge::image2d::system &_image_system,
	boost::filesystem::path const &_base_path,
	sanguis::tools::libmergeimage::aux_::path_vector_vector const &_paths
)
try
{
	FCPPT_ASSERT_PRE(
		!_paths.empty()
	);

	return
		sanguis::tools::libmergeimage::aux_::cell_size(
			sge::image2d::load_exn(
				_image_system,
				_base_path
				/
				_paths[
					0
				].at(
					0
				)
			)->size()
		);
}
catch(
	sge::image::exception const &_error
)
{
	throw
		sanguis::tools::libmergeimage::exception{
			FCPPT_TEXT("Couldn't load an image to determine the cell size: ")
			+
			_error.string()
		};
}
