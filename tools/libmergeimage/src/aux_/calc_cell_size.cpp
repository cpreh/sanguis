#include <sanguis/tools/libmergeimage/aux_/calc_cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector_vector.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::tools::libmergeimage::aux_::cell_size const
sanguis::tools::libmergeimage::aux_::calc_cell_size(
	sge::image2d::system &_image_system,
	sanguis::tools::libmergeimage::aux_::path_vector_vector const &_paths
)
{
	FCPPT_ASSERT_PRE(
		!_paths.empty()
	);

	return
		sanguis::tools::libmergeimage::aux_::cell_size(
			sge::image2d::load_exn(
				_image_system,
				_paths[
					0
				].at(
					0
				)
			)->size()
		);
}
