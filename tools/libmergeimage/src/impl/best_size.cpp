#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <sanguis/tools/libmergeimage/impl/best_size.hpp>
#include <sanguis/tools/libmergeimage/impl/cell_size.hpp>
#include <sanguis/tools/libmergeimage/impl/cells_in_dim.hpp>
#include <sanguis/tools/libmergeimage/impl/max_exponent.hpp>
#include <sanguis/tools/libmergeimage/impl/pow2.hpp>
#include <sge/image/size_type.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::image::size_type
sanguis::tools::libmergeimage::impl::best_size(
	sanguis::tools::libmergeimage::count_type const _count,
	sanguis::tools::libmergeimage::impl::cell_size const _cell_size
)
{
	for(
		sge::image::size_type index(
			0
		);
		index
		<=
		sanguis::tools::libmergeimage::impl::max_exponent::value
		;
		++index
	)
	{
		sge::image::size_type const size(
			sanguis::tools::libmergeimage::impl::pow2(
				index
			)
		);

		if(
			sanguis::tools::libmergeimage::impl::cells_in_dim(
				size,
				_cell_size
			)
			>=
			_count
		)
			return
				size;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
