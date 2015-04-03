#include <sanguis/model/cell_size.hpp>
#include <sanguis/tools/libmergeimage/exception.hpp>
#include <sanguis/tools/libmergeimage/image_vector.hpp>
#include <sanguis/tools/libmergeimage/merge_images.hpp>
#include <sanguis/tools/libmergeimage/merge_result.hpp>
#include <sanguis/tools/libmergeimage/impl/calc_cell_size.hpp>
#include <sanguis/tools/libmergeimage/impl/cell_size.hpp>
#include <sanguis/tools/libmergeimage/impl/gather_paths.hpp>
#include <sanguis/tools/libmergeimage/impl/make_image.hpp>
#include <sanguis/tools/libmergeimage/impl/make_maximum_count.hpp>
#include <sanguis/tools/libmergeimage/impl/merge_paths.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector_vector.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::merge_result
sanguis::tools::libmergeimage::merge_images(
	sge::image2d::system &_image_system,
	boost::filesystem::path const &_base_path
)
{
	sanguis::tools::libmergeimage::impl::path_vector_vector const gathered_paths(
		sanguis::tools::libmergeimage::impl::gather_paths(
			_base_path
		)
	);

	if(
		gathered_paths.empty()
	)
		throw
			sanguis::tools::libmergeimage::exception(
				FCPPT_TEXT("Nothing to do in ")
				+
				fcppt::filesystem::path_to_string(
					_base_path
				)
			);

	sanguis::tools::libmergeimage::impl::cell_size const cell_size(
		sanguis::tools::libmergeimage::impl::calc_cell_size(
			_image_system,
			_base_path,
			gathered_paths
		)
	);

	sanguis::tools::libmergeimage::impl::path_vector_vector const merged_paths(
		sanguis::tools::libmergeimage::impl::merge_paths(
			gathered_paths,
			sanguis::tools::libmergeimage::impl::make_maximum_count(
				cell_size
			)
		)
	);

	return
		sanguis::tools::libmergeimage::merge_result(
			sanguis::model::cell_size(
				fcppt::math::dim::structure_cast<
					sanguis::model::cell_size::value_type,
					fcppt::cast::size_fun
				>(
					cell_size.get()
				)
			),
			fcppt::algorithm::map<
				sanguis::tools::libmergeimage::image_vector
			>(
				merged_paths,
				[
					cell_size,
					&_base_path,
					&_image_system
				](
					sanguis::tools::libmergeimage::impl::path_vector const &_paths
				)
				{
					return
						sanguis::tools::libmergeimage::impl::make_image(
							_image_system,
							_base_path,
							cell_size,
							_paths
						);
				}
			)
		);
}
