#include <sanguis/model/cell_size.hpp>
#include <sanguis/model/dim.hpp>
#include <sanguis/model/object.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/model/optional_image_name.hpp>
#include <sanguis/model/part_map.hpp>
#include <sanguis/tools/libmergeimage/merge_paths.hpp>
#include <sanguis/tools/libmergeimage/symbol.hpp>
#include <fcppt/filesystem/strip_prefix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/range/iterator_range.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


sanguis::model::object
sanguis::tools::libmergeimage::merge_paths(
	boost::filesystem::path const &_base_path
)
{
	typedef
	std::vector<
		boost::filesystem::path
	>
	path_vector;

	path_vector paths;

	for(
		auto const &path
		:
		boost::make_iterator_range(
			boost::filesystem::recursive_directory_iterator(
				_base_path
			),
			boost::filesystem::recursive_directory_iterator()
		)
	)
		paths.push_back(
			fcppt::filesystem::strip_prefix(
				_base_path,
				path
			)
		);

	// TODO:
	return
		sanguis::model::object(
			sanguis::model::cell_size(
				sanguis::model::dim::null()
			),
			sanguis::model::optional_animation_delay(),
			sanguis::model::part_map(),
			sanguis::model::optional_image_name()
		);
}
