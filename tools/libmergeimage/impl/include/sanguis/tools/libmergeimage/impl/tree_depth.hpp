#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_TREE_DEPTH_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_TREE_DEPTH_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sanguis::tools::libmergeimage::impl
{

using tree_depth = std::integral_constant<sanguis::tools::libmergeimage::count_type, 3>;

}

#endif
