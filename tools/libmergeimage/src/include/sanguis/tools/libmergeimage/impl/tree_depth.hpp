#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_TREE_DEPTH_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_IMPL_TREE_DEPTH_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace impl
{

typedef
std::integral_constant<
	sanguis::tools::libmergeimage::count_type,
	3
>
tree_depth;

}
}
}
}

#endif
