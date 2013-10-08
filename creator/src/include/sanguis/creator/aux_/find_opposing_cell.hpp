#ifndef SANGUIS_CREATOR_AUX__FIND_OPPOSING_CELL_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__FIND_OPPOSING_CELL_HPP_INCLUDED

#include <sanguis/creator/aux_/reachable_grid.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <fcppt/optional_impl.hpp>

namespace sanguis
{
namespace creator
{
namespace aux_
{

fcppt::optional<
	sanguis::creator::pos
>
find_opposing_cell(
	sanguis::creator::aux_::reachable_grid &,
	sanguis::creator::pos const &
);

}
}
}

#endif
