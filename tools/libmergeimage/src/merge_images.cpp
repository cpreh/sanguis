#include <sanguis/tools/libmergeimage/image_vector.hpp>
#include <sanguis/tools/libmergeimage/merge_images.hpp>
#include <sanguis/tools/libmergeimage/aux_/calc_cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/gather_paths.hpp>
#include <sanguis/tools/libmergeimage/aux_/make_image.hpp>
#include <sanguis/tools/libmergeimage/aux_/make_maximum_count.hpp>
#include <sanguis/tools/libmergeimage/aux_/merge_paths.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector_vector.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::image_vector
sanguis::tools::libmergeimage::merge_images(
	sge::image2d::system &_image_system,
	boost::filesystem::path const &_base_path
)
{
	sanguis::tools::libmergeimage::aux_::path_vector_vector const gathered_paths(
		sanguis::tools::libmergeimage::aux_::gather_paths(
			_base_path
		)
	);

	if(
		gathered_paths.empty()
	)
		return
			sanguis::tools::libmergeimage::image_vector();

	sanguis::tools::libmergeimage::aux_::cell_size const cell_size(
		sanguis::tools::libmergeimage::aux_::calc_cell_size(
			_image_system,
			gathered_paths
		)
	);

	sanguis::tools::libmergeimage::aux_::path_vector_vector const merged_paths(
		sanguis::tools::libmergeimage::aux_::merge_paths(
			gathered_paths,
			sanguis::tools::libmergeimage::aux_::make_maximum_count(
				cell_size
			)
		)
	);

	return
		fcppt::algorithm::map<
			sanguis::tools::libmergeimage::image_vector
		>(
			merged_paths,
			[
				cell_size,
				&_base_path,
				&_image_system
			](
				sanguis::tools::libmergeimage::aux_::path_vector const &_paths
			)
			{
				return
					sanguis::tools::libmergeimage::aux_::make_image(
						_image_system,
						_base_path,
						cell_size,
						_paths
					);
			}
		);
}
