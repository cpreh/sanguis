#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/find_opposing_cell.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/optional/object_impl.hpp>


// Finds an empty neighboring cell in the grid that isn't
// already part of the maze. There should at most be one
// such cell.
fcppt::optional::object<
	sanguis::creator::pos
>
sanguis::creator::impl::find_opposing_cell
(
	sanguis::creator::impl::reachable_grid const &grid,
	sanguis::creator::pos const &cell
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
	{
		return fcppt::optional::object<
			sanguis::creator::pos
		>();
	}

	for(
		auto const &n
		:
		fcppt::container::grid::neumann_neighbors(
			cell)

	)
	{
		sanguis::creator::pos const opposite(
			cell
			-
			(
				n
				-
				cell
			)
		);

		if(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::grid::at_optional(
					grid,
					n
				)
			).get()
			==
			sanguis::creator::impl::reachable(true)
		)
		{
			return
				FCPPT_ASSERT_OPTIONAL_ERROR(
					fcppt::container::grid::at_optional(
						grid,
						opposite
					)
				).get()
				==
				sanguis::creator::impl::reachable(true)
				?
					fcppt::optional::object<
						sanguis::creator::pos
					>()
				:
					fcppt::optional::object<
						sanguis::creator::pos
					>(
						opposite
					);
		}
	}

	FCPPT_ASSERT_UNREACHABLE;
}
