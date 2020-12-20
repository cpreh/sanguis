#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <sanguis/tools/libmergeimage/impl/cell_size.hpp>
#include <sanguis/tools/libmergeimage/impl/cells_in_dim.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image2d/dim.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/fill.hpp>


sanguis::tools::libmergeimage::count_type
sanguis::tools::libmergeimage::impl::cells_in_dim(
	sge::image::size_type const _size,
	sanguis::tools::libmergeimage::impl::cell_size const &_cell_size
)
{
	return
		fcppt::math::dim::contents(
			(
				fcppt::math::dim::fill<
					sge::image2d::dim
				>(
					_size
				)
				/
				(
					_cell_size.get()
					+
					fcppt::math::dim::fill<
						sge::image2d::dim
					>(
						1U
					)
				)
			).get_unsafe()
		);
}
