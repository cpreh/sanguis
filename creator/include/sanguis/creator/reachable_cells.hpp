#ifndef SANGUIS_CREATOR_REACHABLE_CELLS_HPP_INCLUDED
#define SANGUIS_CREATOR_REACHABLE_CELLS_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace creator
{

std::vector<
	sanguis::creator::pos
>
reachable_cells(
	sanguis::creator::grid const &,
	sanguis::creator::pos const,
	sanguis::creator::difference_type const);

}
}

#endif
