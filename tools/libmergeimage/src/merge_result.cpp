#include <sanguis/model/cell_size.hpp>
#include <sanguis/tools/libmergeimage/image_vector.hpp>
#include <sanguis/tools/libmergeimage/merge_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::tools::libmergeimage::merge_result::merge_result(
	sanguis::model::cell_size const _cell_size,
	sanguis::tools::libmergeimage::image_vector &&_images
)
:
	cell_size_(
		_cell_size
	),
	images_(
		std::move(
			_images
		)
	)
{
}

sanguis::tools::libmergeimage::merge_result::merge_result(
	merge_result &&
) = default;

sanguis::tools::libmergeimage::merge_result &
sanguis::tools::libmergeimage::merge_result::operator=(
	merge_result &&
) = default;

sanguis::tools::libmergeimage::merge_result::~merge_result()
{
}

sanguis::model::cell_size const
sanguis::tools::libmergeimage::merge_result::cell_size() const
{
	return
		cell_size_;
}

sanguis::tools::libmergeimage::image_vector const &
sanguis::tools::libmergeimage::merge_result::images() const
{
	return
		images_;
}
