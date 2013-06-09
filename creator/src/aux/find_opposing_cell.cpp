#include <sanguis/creator/aux/find_opposing_cell.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux/neumann_neighbors.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fcppt/config/external_end.hpp>


// Finds an empty neighboring cell in the grid that isn't
// already part of the maze. There should at most be one
// such cell.
fcppt::optional<
	sanguis::creator::grid::pos
>
sanguis::creator::aux::find_opposing_cell
(
	sanguis::creator::grid &grid,
	std::vector<
		sanguis::creator::grid::pos
	> &maze,
	sanguis::creator::grid::pos const &cell
)
{

	// discard border tiles
	if (
		cell.x() == grid.size().w() - 1
		||
		cell.x() == 0
		||
		cell.y() == grid.size().h() - 1
		||
		cell.y() == 0
		)
		return fcppt::optional<
			sanguis::creator::grid::pos
		>();

	std::vector<
		sanguis::creator::grid::pos
	>
	neighbors =
		sanguis::creator::aux::neumann_neighbors(
			cell
		);

	std::vector<
		sanguis::creator::grid::pos
	>
	candidates;

	// all empty neighboring cells are candidates for the
	// kind of cell we're looking for
	std::copy_if(
		neighbors.begin(),
		neighbors.end(),
		std::back_inserter(candidates),
		[&grid](
			sanguis::creator::grid::pos &elem
		)
		{
			return
				grid[elem]
					==
				sanguis::creator::tile::nothing;
		}
	);

	// this should never happen, if the algorithm is correct
	// only border tiles could have fewer neighbors but they
	// were discarded already
	FCPPT_ASSERT_ERROR(
		candidates.size() == 2);

	if(!fcppt::algorithm::contains(maze, candidates[0]))
		return fcppt::optional<
			sanguis::creator::grid::pos
		>(candidates[0]);

	if(!fcppt::algorithm::contains(maze, candidates[1]))
		return fcppt::optional<
			sanguis::creator::grid::pos
		>(candidates[1]);

	return fcppt::optional<
		sanguis::creator::grid::pos
	>();
}
