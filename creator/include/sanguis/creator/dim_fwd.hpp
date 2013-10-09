#ifndef SANGUIS_CREATOR_DIM_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_DIM_FWD_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/container/grid/dim_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::grid::dim<
	sanguis::creator::size_type,
	2u
> dim;

}
}

#endif
