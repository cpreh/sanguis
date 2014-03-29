#include <sanguis/tools/libmergeimage/aux_/cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/cells_in_dim.hpp>
#include <sanguis/tools/libmergeimage/aux_/count_maximum.hpp>
#include <sanguis/tools/libmergeimage/aux_/make_maximum_count.hpp>
#include <sanguis/tools/libmergeimage/aux_/max_exponent.hpp>
#include <sanguis/tools/libmergeimage/aux_/pow2.hpp>


sanguis::tools::libmergeimage::aux_::count_maximum
sanguis::tools::libmergeimage::aux_::make_maximum_count(
	sanguis::tools::libmergeimage::aux_::cell_size const _cell_size
)
{
	return
		sanguis::tools::libmergeimage::aux_::count_maximum(
			sanguis::tools::libmergeimage::aux_::cells_in_dim(
				sanguis::tools::libmergeimage::aux_::pow2(
					sanguis::tools::libmergeimage::aux_::max_exponent::value
				),
				_cell_size
			)
		);
}
