#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_BEST_SIZE_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_BEST_SIZE_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <sanguis/tools/libmergeimage/impl/cell_size.hpp>
#include <sge/image/size_type.hpp>


namespace sanguis::tools::libmergeimage::impl
{

sge::image::size_type
best_size(
	sanguis::tools::libmergeimage::count_type,
	sanguis::tools::libmergeimage::impl::cell_size const &
);

}

#endif
