#include <sanguis/creator/reachable_cells.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

std::vector<
	sanguis::creator::pos
>
sanguis::creator::reachable_cells(
	sanguis::creator::grid const &_grid,
	sanguis::creator::pos const _origin,
	sanguis::creator::difference_type const _radius)
{
	std::vector<sanguis::creator::pos> ret;
}
