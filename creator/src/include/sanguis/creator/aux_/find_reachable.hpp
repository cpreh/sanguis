#ifndef SANGUIS_CREATOR_AUX__FIND_REACHABLE_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__FIND_REACHABLE_HPP_INCLUDED

#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/aux_/reachable_grid.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

sanguis::creator::aux_::reachable_grid
find_reachable(
	sanguis::creator::grid const &,
	sanguis::creator::pos const
);

}
}
}

#endif
