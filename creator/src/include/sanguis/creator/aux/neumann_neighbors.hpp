#ifndef SANGUIS_CREATOR_AUX_NEUMANN_NEIGHBORS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_NEUMANN_NEIGHBORS_HPP_INCLUDED

#include <vector>
#include <sanguis/creator/grid.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{

std::vector<
	sanguis::creator::grid::dim
>
neumann_neighbors(
	sanguis::creator::grid::dim const &
);

}
}
}

#endif
