#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_MERGE_PATHS_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_MERGE_PATHS_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/impl/count_maximum.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector_vector.hpp>


namespace sanguis::tools::libmergeimage::impl
{

sanguis::tools::libmergeimage::impl::path_vector_vector
merge_paths(
	sanguis::tools::libmergeimage::impl::path_vector_vector const &,
	sanguis::tools::libmergeimage::impl::count_maximum
);

}

#endif
