#ifndef SANGUIS_CREATOR_AUX_FIND_OPPOSING_CELL_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_FIND_OPPOSING_CELL_HPP_INCLUDED

#include <sanguis/creator/grid.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{

fcppt::optional<
	sanguis::creator::grid::pos
>
find_opposing_cell(
	sanguis::creator::grid &,
	std::vector<
		sanguis::creator::grid::pos
	> &,
	sanguis::creator::grid::pos const &
);

}
}
}

#endif
