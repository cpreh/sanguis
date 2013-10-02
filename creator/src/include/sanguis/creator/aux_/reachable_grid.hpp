#ifndef SANGUIS_CREATOR_AUX__REACHABLE_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__REACHABLE_GRID_HPP_INCLUDED

#include <fcppt/container/grid/object.hpp>
#include <sanguis/creator/aux_/reachable.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>

namespace sanguis
{
namespace creator
{
namespace aux_
{

fcppt::container::grid::object<
	sanguis::creator::aux_::reachable,
	2
>
reachable_grid(
	sanguis::creator::grid const &,
	sanguis::creator::pos const
);

}
}
}

#endif
