#ifndef SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__CELL_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_TOOLS_LIBMERGEIMAGE_AUX__CELL_SIZE_FWD_HPP_INCLUDED

#include <sge/image2d/dim_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis
{
namespace tools
{
namespace libmergeimage
{
namespace aux_
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::image2d::dim,
	cell_size
);

}
}
}
}

#endif
