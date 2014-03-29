#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__MERGE_PATHS_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__MERGE_PATHS_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/aux_/count_maximum.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector_vector.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace aux_
{

sanguis::tools::libmergeimage::aux_::path_vector_vector
merge_paths(
	sanguis::tools::libmergeimage::aux_::path_vector_vector const &,
	sanguis::tools::libmergeimage::aux_::count_maximum
);

}
}
}
}

#endif
