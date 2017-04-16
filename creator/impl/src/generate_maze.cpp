#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
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
#include <fcppt/algorithm/append.hpp>
#include <fcppt/algorithm/remove.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <vector>
#include <fcppt/config/external_end.hpp>


// this is a maze generator that follows the algorithm described at
// http://en.wikipedia.org/w/index.php?title=Maze_generation_algorithm&oldid=550777074#Randomized_Prim.27s_algorithm

sanguis::creator::impl::maze_result
sanguis::creator::impl::generate_maze(
	sanguis::creator::impl::reachable_grid &_maze,
	sanguis::creator::impl::random::generator &_randgen
)
{
	auto size = _maze.size();

	sanguis::creator::impl::random::uniform_size_variate
	random_index(
		_randgen,
		sanguis::creator::impl::random::uniform_size(
			sanguis::creator::impl::random::uniform_size::param_type::min(
				0u
			),
			sanguis::creator::impl::random::uniform_size::param_type::max(
				// TODO: unsigned?
				std::numeric_limits<unsigned>::max()
		)));

	using std::vector;
	using sanguis::creator::pos;

	auto res_grid =
		sanguis::creator::impl::region_grid{
			_maze.size(),
			// walls
			region_id{
				-1
			}
		};

	auto cur_region =
		region_id{
			0
		};

	while (true){
		auto tmp_pos = pos{
			sanguis::creator::impl::random::uniform_pos{
				_randgen,
				size
			}()
		};

		auto maybe_starting_pos = find_closest(
			_maze,
			tmp_pos,
			// potential spaces lie on every other row and column and aren't
			// carved out yet
			[
				&_maze
			]
			(
				pos const _a
			)
			{
				return
							_maze[
								_a
							]
						==
							sanguis::creator::impl::reachable(
								false
							)
					&&
								_a.x()
							%
								2
						==
							1
					&&
								_a.y()
							%
								2
						==
							1;
			},
			fcppt::optional::object<
				sanguis::creator::pos::value_type
			>{}
		);

		if (!maybe_starting_pos.has_value())
			break;

		pos const
		starting_pos =
		FCPPT_ASSERT_OPTIONAL_ERROR(
			maybe_starting_pos
		);

		_maze[
			starting_pos
		] =
			sanguis::creator::impl::reachable(true);

		res_grid[
			starting_pos
		] =
			cur_region;

		// wall tiles that are to be processed next
		vector<
			pos
		> walls;

		// initially populate the set of walls with the neighbors
		// of the starting point
		auto neighbors =
			fcppt::container::grid::neumann_neighbors(
				starting_pos);

		fcppt::algorithm::append(
			walls,
			neighbors);

		while(
			!walls.empty()
		)
		{
			auto const random_wall =
				walls[
					random_index() %
					walls.size()
				];

			sanguis::creator::impl::optional_pos const
			opposing_cell{
				sanguis::creator::impl::find_opposing_cell(
					_maze,
					random_wall
				)
			};

			fcppt::optional::maybe_void(
				opposing_cell,
				[
					&
				](
					pos const _opposing_cell
				)
				{
					_maze[
						random_wall
					] =
						sanguis::creator::impl::reachable(true);

					_maze[
						_opposing_cell
					] =
						sanguis::creator::impl::reachable(true);

					res_grid[
						random_wall
					] = cur_region;
					res_grid[
						_opposing_cell
					] = cur_region;

					// this actually appends some cells that aren't walls,
					// but they get filtered away the next time, since they
					// have two empty neighbors
					fcppt::algorithm::append(
						walls,
						fcppt::container::grid::neumann_neighbors(
							_opposing_cell
						)
					);
				}
			);

			fcppt::algorithm::remove(
				walls,
				random_wall
			);
		}

		cur_region++;
	}

	return maze_result{
		res_grid,
		cur_region
	};
}
