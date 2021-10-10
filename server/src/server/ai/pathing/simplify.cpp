#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/optional_pos.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/pathing/can_walk_diagonally.hpp>
#include <sanguis/server/ai/pathing/simplify.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_multi.hpp>

sanguis::server::ai::pathing::trail sanguis::server::ai::pathing::simplify(
    sanguis::server::ai::pathing::trail const &_trail, sanguis::creator::grid const &_grid)
{
  return fcppt::optional::maybe(
      fcppt::optional::copy_value(fcppt::container::maybe_front(_trail)),
      [] { return sanguis::server::ai::pathing::trail(); },
      [&_grid, &_trail](sanguis::creator::pos const &_start)
      {
        return fcppt::container::join(
            sanguis::server::ai::pathing::trail{_start},
            fcppt::algorithm::map_optional<sanguis::server::ai::pathing::trail>(
                fcppt::make_int_range_count(_trail.size() - 1U),
                [&_grid, &_trail](sanguis::server::ai::pathing::trail::size_type const _index)
                {
                  sanguis::creator::optional_pos const next1(fcppt::optional::copy_value(
                      fcppt::container::at_optional(_trail, _index + 1U)));

                  sanguis::creator::optional_pos const next2(fcppt::optional::copy_value(
                      fcppt::container::at_optional(_trail, _index + 2U)));

                  return fcppt::optional::maybe_multi(
                      []
                      {
                        // In this case, next1 is set to the node the entity is on.
                        return sanguis::creator::optional_pos();
                      },
                      [_index, &_grid, &_trail](
                          sanguis::creator::pos const &_next1, sanguis::creator::pos const &_next2)
                      {
                        return sanguis::server::ai::pathing::can_walk_diagonally(
                                   _grid, _trail[_index], _next1, _next2)
                                   ? sanguis::creator::optional_pos(_next1)
                                   : sanguis::creator::optional_pos();
                      },
                      next1,
                      next2);
                }));
      });
}
