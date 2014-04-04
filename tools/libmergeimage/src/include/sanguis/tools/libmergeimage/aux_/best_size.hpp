#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__BEST_SIZE_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__BEST_SIZE_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <sanguis/tools/libmergeimage/aux_/cell_size.hpp>
#include <sge/image/size_type.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace aux_
{

sge::image::size_type
best_size(
	sanguis::tools::libmergeimage::count_type,
	sanguis::tools::libmergeimage::aux_::cell_size
);

}
}
}
}

#endif
