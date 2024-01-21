#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/impl/find_reachable.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <fcppt/not.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>
#include <fcppt/container/pop_back.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/container/grid/object.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

sanguis::creator::impl::reachable_grid sanguis::creator::impl::find_reachable(
    sanguis::creator::grid const &_grid, sanguis::creator::pos const &_start)
{
  sanguis::creator::impl::reachable_grid result(
      sanguis::creator::impl::reachable_grid::dim(_grid.size()),
      sanguis::creator::impl::reachable(false));

  std::vector<sanguis::creator::pos> queue{_start};

  while (!queue.empty())
  {
    sanguis::creator::pos const pos{fcppt::optional::to_exception(
        fcppt::container::pop_back(queue),
        [] { return sanguis::creator::exception{FCPPT_TEXT("Queue empty.")}; })};

    fcppt::optional::to_exception(
        fcppt::container::grid::at_optional(result, pos),
        [] { return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")}; })
        .get() = sanguis::creator::impl::reachable{true};

    for (auto const &n : fcppt::container::grid::neumann_neighbors(pos))
    {
      if (fcppt::optional::to_exception(
              fcppt::container::grid::at_optional(result, n),
              [] {
                return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")};
              }).get() == sanguis::creator::impl::reachable{false} &&
          fcppt::not_(sanguis::creator::tile_is_solid(
              fcppt::optional::to_exception(
                  fcppt::container::grid::at_optional(_grid, n),
                  [] { return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")}; })
                  .get())))
      {
        queue.push_back(n);
      }
    }
  }

  return result;
}
