#include <sanguis/creator/aux/neumann_neighbors.hpp>
#include <sanguis/creator/grid.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


// returns the points in the von-Neumann-neighborhood
// of the given cell,
// no range checks are being performed!
std::vector<
	sanguis::creator::grid::pos
>
sanguis::creator::aux::neumann_neighbors(
	sanguis::creator::grid::pos const &cell
)
{
	std::vector<sanguis::creator::grid::pos> ret{
			sanguis::creator::grid::pos{
				cell.x() - 1,
				cell.y()
			},
			sanguis::creator::grid::pos{
				cell.x() + 1,
				cell.y()
			},
			sanguis::creator::grid::pos{
				cell.x(),
				cell.y() - 1,
			},
			sanguis::creator::grid::pos{
				cell.x(),
				cell.y() + 1
			}
		};

	return ret;
}
