#ifndef SANGUIS_CREATOR_AUX__REACHABLE_GRID_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__REACHABLE_GRID_HPP_INCLUDED

#include <fcppt/container/grid/object.hpp>
#include <sanguis/creator/aux_/reachable.hpp>

namespace sanguis
{
namespace creator
{
namespace aux_
{

typedef
fcppt::container::grid::object<
	sanguis::creator::aux_::reachable,
	2
>
reachable_grid;

}
}
}

#endif
