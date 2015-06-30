#ifndef SANGUIS_CREATOR_MIN_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_MIN_FWD_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <fcppt/container/grid/min_from_pos_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::grid::min_from_pos<
	sanguis::creator::pos
>
min;

}
}

#endif
