#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/aux/neighbor_array.hpp>
#include <sanguis/creator/aux/neumann_neighbors.hpp>


// returns the points in the von-Neumann-neighborhood
// of the given cell,
// no range checks are being performed!
sanguis::creator::aux::neighbor_array const
sanguis::creator::aux::neumann_neighbors(
	sanguis::creator::pos const _cell
)
{
	return
		sanguis::creator::aux::neighbor_array{{
			sanguis::creator::pos{
				_cell.x() - 1,
				_cell.y()
			},
			sanguis::creator::pos{
				_cell.x() + 1,
				_cell.y()
			},
			sanguis::creator::pos{
				_cell.x(),
				_cell.y() - 1,
			},
			sanguis::creator::pos{
				_cell.x(),
				_cell.y() + 1
			}
		}};
}
