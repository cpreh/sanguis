#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__CALC_CELL_SIZE_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__CALC_CELL_SIZE_HPP_INCLUDED

#include <sanguis/tools/libmergeimage/aux_/cell_size.hpp>
#include <sanguis/tools/libmergeimage/aux_/path_vector_vector.hpp>
#include <sge/image2d/system_fwd.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace aux_
{

sanguis::tools::libmergeimage::aux_::cell_size const
calc_cell_size(
	sge::image2d::system &,
	sanguis::tools::libmergeimage::aux_::path_vector_vector const &
);

}
}
}
}

#endif
