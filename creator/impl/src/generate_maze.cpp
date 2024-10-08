#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/impl/find_closest.hpp>
#include <sanguis/creator/impl/find_opposing_cell.hpp>
#include <sanguis/creator/impl/generate_maze.hpp>
#include <sanguis/creator/impl/maze_result.hpp>
#include <sanguis/creator/impl/optional_pos.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <sanguis/creator/impl/region_grid.hpp>
#include <sanguis/creator/impl/region_id.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_pos.hpp>
#include <sanguis/creator/impl/random/uniform_size.hpp>
#include <sanguis/creator/impl/random/uniform_size_variate.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>
#include <fcppt/algorithm/remove.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

// this is a maze generator that follows the algorithm described at
// http://en.wikipedia.org/w/index.php?title=Maze_generation_algorithm&oldid=550777074#Randomized_Prim.27s_algorithm

sanguis::creator::impl::maze_result sanguis::creator::impl::generate_maze(
    fcppt::reference<sanguis::creator::impl::reachable_grid> const _maze,
    sanguis::creator::impl::random::generator &_randgen)
{
  auto size = _maze.get().size();

  sanguis::creator::impl::random::uniform_size_variate random_index(
      fcppt::make_ref(_randgen),
      sanguis::creator::impl::random::uniform_size(
          sanguis::creator::impl::random::uniform_size::param_type::min(0U),
          sanguis::creator::impl::random::uniform_size::param_type::max(
              std::numeric_limits<unsigned>::max())));

  auto res_grid = sanguis::creator::impl::region_grid{
      size,
      // walls
      region_id{-1}};

  auto cur_region = region_id{0};

  while (true)
  {
    sanguis::creator::pos const tmp_pos{
        sanguis::creator::impl::random::uniform_pos{fcppt::make_ref(_randgen), size}()};

    auto maybe_starting_pos = sanguis::creator::impl::find_closest(
        _maze.get(),
        tmp_pos,
        // potential spaces lie on every other row and column and aren't
        // carved out yet
        [](pos const &_a, sanguis::creator::impl::reachable const &_r) {
          return _r == sanguis::creator::impl::reachable(false) && _a.x() % 2 == 1 &&
                 _a.y() % 2 == 1;
        },
        fcppt::optional::object<sanguis::creator::pos::value_type>{});

    if (!maybe_starting_pos.has_value())
    {
      break;
    }

    sanguis::creator::pos const starting_pos{fcppt::optional::to_exception(
        maybe_starting_pos,
        [] { return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")}; })};

    fcppt::optional::to_exception(
        fcppt::container::grid::at_optional(_maze.get(), starting_pos),
        [] { return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")}; })
        .get() = sanguis::creator::impl::reachable(true);

    fcppt::optional::to_exception(
        fcppt::container::grid::at_optional(res_grid, starting_pos),
        [] { return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")}; })
        .get() = cur_region;

    // wall tiles that are to be processed next
    std::vector<sanguis::creator::pos> walls;

    walls = fcppt::container::join(
        std::move(walls),
        // initially populate the set of walls with the neighbors
        // of the starting point
        fcppt::container::grid::neumann_neighbors(starting_pos));

    while (!walls.empty())
    {
      auto const random_wall = walls[random_index() % walls.size()];

      sanguis::creator::impl::optional_pos const opposing_cell{
          sanguis::creator::impl::find_opposing_cell(_maze.get(), random_wall)};

      fcppt::optional::maybe_void(
          opposing_cell,
          [&](pos const &_opposing_cell)
          {
            fcppt::optional::to_exception(
                fcppt::container::grid::at_optional(_maze.get(), random_wall),
                [] { return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")}; })
                .get() = sanguis::creator::impl::reachable(true);

            fcppt::optional::to_exception(
                fcppt::container::grid::at_optional(_maze.get(), _opposing_cell),
                [] { return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")}; })
                .get() = sanguis::creator::impl::reachable(true);

            fcppt::optional::to_exception(
                fcppt::container::grid::at_optional(res_grid, random_wall),
                [] { return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")}; })
                .get() = cur_region;

            fcppt::optional::to_exception(
                fcppt::container::grid::at_optional(res_grid, _opposing_cell),
                [] { return sanguis::creator::exception{FCPPT_TEXT("Pos out of range!")}; })
                .get() = cur_region;

            // this actually appends some cells that aren't walls,
            // but they get filtered away the next time, since they
            // have two empty neighbors
            walls = fcppt::container::join(
                std::move(walls), fcppt::container::grid::neumann_neighbors(_opposing_cell));
          });

      fcppt::algorithm::remove(walls, random_wall);
      }

      cur_region++;
    }

  return maze_result{.grid = res_grid, .next_id = cur_region};
}
