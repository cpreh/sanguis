#include <sanguis/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/server/ai/pathing/find_target.hpp>
#include <sanguis/server/ai/pathing/optional_trail.hpp>
#include <sanguis/server/ai/pathing/start.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/std_hash.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <queue>
#include <unordered_map>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::ai::pathing::optional_trail sanguis::server::ai::pathing::find_target(
    sanguis::creator::grid const &_grid,
    sanguis::server::ai::pathing::start const &_start,
    sanguis::server::ai::pathing::target const &_target)
{
  using pos_queue = std::queue<sanguis::creator::pos>;

  using predecessor_map = std::unordered_map<sanguis::creator::pos, sanguis::creator::pos>;

  predecessor_map predecessors;

  predecessors.insert(std::make_pair(_start.get(), _start.get()));

  pos_queue positions;

  positions.push(_start.get());

  while (!positions.empty())
  {
    sanguis::creator::pos const cur(positions.front());

    if (cur == _target.get())
    {
      sanguis::server::ai::pathing::trail result{cur};

      for (sanguis::creator::pos trail_pos(cur); trail_pos != _start.get();
           trail_pos = result.back())
      {
        result.push_back(fcppt::optional::to_exception(
                             fcppt::container::find_opt_mapped(predecessors, trail_pos),
                             [] { return sanguis::exception{FCPPT_TEXT("Trail pos not found!")}; })
                             .get());
      }

      return sanguis::server::ai::pathing::optional_trail{std::move(result)};
    }

    positions.pop();

    for (sanguis::creator::pos const &pos : fcppt::container::grid::neumann_neighbors(cur))
    {
      if (!fcppt::container::find_opt(predecessors, pos).has_value() &&
          fcppt::optional::maybe(
              fcppt::container::grid::at_optional(_grid, pos),
              fcppt::const_(false),
              [](fcppt::reference<sanguis::creator::tile const> const _tile)
              { return !sanguis::creator::tile_is_solid(_tile.get()); }))
      {
        positions.push(pos);

        predecessors.insert(std::make_pair(pos, cur));
      }
    }
  }

  return sanguis::server::ai::pathing::optional_trail{};
}
