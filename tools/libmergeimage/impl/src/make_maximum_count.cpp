#include <sanguis/tools/libmergeimage/impl/cell_size.hpp>
#include <sanguis/tools/libmergeimage/impl/cells_in_dim.hpp>
#include <sanguis/tools/libmergeimage/impl/count_maximum.hpp>
#include <sanguis/tools/libmergeimage/impl/make_maximum_count.hpp>
#include <sanguis/tools/libmergeimage/impl/max_exponent.hpp>
#include <sanguis/tools/libmergeimage/impl/pow2.hpp>

sanguis::tools::libmergeimage::impl::count_maximum
sanguis::tools::libmergeimage::impl::make_maximum_count(
    sanguis::tools::libmergeimage::impl::cell_size const &_cell_size)
{
  return sanguis::tools::libmergeimage::impl::count_maximum(
      sanguis::tools::libmergeimage::impl::cells_in_dim(
          sanguis::tools::libmergeimage::impl::pow2(
              sanguis::tools::libmergeimage::impl::max_exponent::value),
          _cell_size));
}
