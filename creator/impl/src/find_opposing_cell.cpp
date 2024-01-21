#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/impl/find_opposing_cell.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>

// Finds an empty neighboring cell in the grid that isn't
// already part of the maze. There should at most be one
// such cell.
fcppt::optional::object<sanguis::creator::pos> sanguis::creator::impl::find_opposing_cell(
    sanguis::creator::impl::reachable_grid const &grid, sanguis::creator::pos const &cell)
{
  // discard border tiles
  if (cell.x() == grid.size().w() - 1 || cell.x() == 0 || cell.y() == grid.size().h() - 1 ||
      cell.y() == 0)
  {
    return fcppt::optional::object<sanguis::creator::pos>();
  }

  for (auto const &n : fcppt::container::grid::neumann_neighbors(cell))
  {
    sanguis::creator::pos const opposite{cell - (n - cell)};

    if (fcppt::optional::to_exception(
            fcppt::container::grid::at_optional(grid, n),
            [] { return sanguis::creator::exception{FCPPT_TEXT("Grid out of range!")}; })
            .get() == sanguis::creator::impl::reachable(true))
    {
      return fcppt::optional::to_exception(
                 fcppt::container::grid::at_optional(grid, opposite),
                 [] {
                   return sanguis::creator::exception{
                       FCPPT_TEXT("Opposite position out of range!")};
                 }).get() == sanguis::creator::impl::reachable(true)
                 ? fcppt::optional::object<sanguis::creator::pos>()
                 : fcppt::optional::object<sanguis::creator::pos>(opposite);
    }
  }

  return fcppt::optional::object<sanguis::creator::pos>{};
}
