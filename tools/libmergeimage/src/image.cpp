#include <sanguis/tools/libmergeimage/image.hpp>
#include <sanguis/tools/libmergeimage/image_store.hpp>
#include <sanguis/tools/libmergeimage/path_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::image::image(
	sanguis::tools::libmergeimage::path_vector &&_paths,
	sanguis::tools::libmergeimage::image_store &&_store
)
:
	paths_(
		std::move(
			_paths
		)
	),
	store_(
		std::move(
			_store
		)
	)
{
}

sanguis::tools::libmergeimage::image::image(
	sanguis::tools::libmergeimage::path_vector const &_paths,
	sanguis::tools::libmergeimage::image_store &&_store
)
:
	paths_(
		_paths
	),
	store_(
		std::move(
			_store
		)
	)
{
}

sanguis::tools::libmergeimage::image::image(
	image &&
) = default;

sanguis::tools::libmergeimage::image &
sanguis::tools::libmergeimage::image::operator=(
	image &&
) = default;

sanguis::tools::libmergeimage::image::~image()
{
}

sanguis::tools::libmergeimage::path_vector const &
sanguis::tools::libmergeimage::image::paths() const
{
	return
		paths_;
}

sanguis::tools::libmergeimage::image_store const &
sanguis::tools::libmergeimage::image::store() const
{
	return
		store_;
}
