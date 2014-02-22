#ifndef SANGUIS_MODEL_CELL_SIZE_FWD_HPP_INCLUDED
#define SANGUIS_MODEL_CELL_SIZE_FWD_HPP_INCLUDED

#include <sge/image2d/dim_fwd.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sanguis
{
namespace model
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::image2d::dim,
	cell_size
);

}
}

#endif
