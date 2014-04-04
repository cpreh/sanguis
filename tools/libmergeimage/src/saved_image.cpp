#include <sanguis/model/image_name.hpp>
#include <sanguis/tools/libmergeimage/path_count_pair_vector.hpp>
#include <sanguis/tools/libmergeimage/saved_image.hpp>


sanguis::tools::libmergeimage::saved_image::saved_image(
	sanguis::tools::libmergeimage::path_count_pair_vector const &_paths,
	sanguis::model::image_name const &_image_name
)
:
	paths_(
		_paths
	),
	image_name_(
		_image_name
	)
{
}

sanguis::tools::libmergeimage::path_count_pair_vector const &
sanguis::tools::libmergeimage::saved_image::paths() const
{
	return
		paths_;
}

sanguis::model::image_name const &
sanguis::tools::libmergeimage::saved_image::image_name() const
{
	return
		image_name_;
}
