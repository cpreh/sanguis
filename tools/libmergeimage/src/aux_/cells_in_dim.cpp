#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <sanguis/tools/libmergeimage/aux_/cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/cells_in_dim.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image2d/dim.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::tools::libmergeimage::count_type
sanguis::tools::libmergeimage::aux_::cells_in_dim(
	sge::image::size_type const _size,
	sanguis::tools::libmergeimage::aux_::cell_size const _cell_size
)
{
	return
		(
			fcppt::math::dim::fill<
				sge::image2d::dim::dim_wrapper::value
			>(
				_size
			)
			/
			(
				_cell_size.get()
				+
				1u
			)
		).content();
}
