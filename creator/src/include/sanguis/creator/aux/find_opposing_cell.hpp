#ifndef SANGUIS_CREATOR_AUX_FIND_OPPOSING_CELL_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_FIND_OPPOSING_CELL_HPP_INCLUDED

#include <sanguis/creator/grid.hpp>
#include <fcppt/optional.hpp>
#include <vector>


namespace sanguis
{
namespace creator
{
namespace aux
{

fcppt::optional<
	sanguis::creator::grid::dim
>
find_opposing_cell(
	sanguis::creator::grid &,
	std::vector<
		sanguis::creator::grid::dim
	> &,
	sanguis::creator::grid::dim const &
);

}
}
}

#endif
