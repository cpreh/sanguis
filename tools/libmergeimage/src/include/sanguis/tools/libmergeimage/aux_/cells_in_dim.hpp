#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__CELLS_IN_DIM_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__CELLS_IN_DIM_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/count_type.hpp>
#include <sanguis/tools/libmergeimage/aux_/cell_size_fwd.hpp>
#include <sge/image/size_type.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace aux_
{

sanguis::tools::libmergeimage::count_type
cells_in_dim(
	sge::image::size_type,
	sanguis::tools::libmergeimage::aux_::cell_size
);

}
}
}
}

#endif
