#ifndef SANGUIS_CREATOR_AUX_NEUMANN_NEIGHBORS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_NEUMANN_NEIGHBORS_HPP_INCLUDED

#include <sanguis/creator/grid.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{

std::vector<
	sanguis::creator::grid::pos
>
neumann_neighbors(
	sanguis::creator::grid::pos const &
);

}
}
}

#endif
