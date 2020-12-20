#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_FOLD_PATHS_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_FOLD_PATHS_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/path_count_pair_vector.hpp>
#include <sanguis/tools/libmergeimage/impl/path_vector.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace impl
{

sanguis::tools::libmergeimage::path_count_pair_vector
fold_paths(
	sanguis::tools::libmergeimage::impl::path_vector const &
);

}
}
}
}

#endif
