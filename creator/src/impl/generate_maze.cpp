#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/impl/find_opposing_cell.hpp>
#include <sanguis/creator/impl/generate_maze.hpp>
#include <sanguis/creator/impl/optional_pos.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_size.hpp>
#include <sanguis/creator/impl/random/uniform_size_variate.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/algorithm/remove.hpp>
#include <fcppt/container/grid/make_pos_crange.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <vector>
#include <fcppt/config/external_end.hpp>


// this is a maze generator that follows the algorithm described at
// http://en.wikipedia.org/w/index.php?title=Maze_generation_algorithm&oldid=550777074#Randomized_Prim.27s_algorithm
sanguis::creator::grid
sanguis::creator::impl::generate_maze(
	sanguis::creator::dim const &size,
	unsigned const wall_thickness,
	unsigned const spacing,
	sanguis::creator::tile const empty,
	sanguis::creator::tile const wall,
	sanguis::creator::impl::random::generator &randgen
)
{
	sanguis::creator::impl::reachable_grid
	raw_maze(
		size,
		sanguis::creator::impl::reachable(
			false)
	);

	sanguis::creator::impl::random::uniform_size_variate
	random_index(
		randgen,
		sanguis::creator::impl::random::uniform_size(
			sanguis::creator::impl::random::uniform_size::param_type::min(
				0u
			),
			sanguis::creator::impl::random::uniform_size::param_type::max(
				// TODO: unsigned?
				std::numeric_limits<unsigned>::max()
		)));

	sanguis::creator::impl::random::uniform_size_variate
	random_x(
		randgen,
		sanguis::creator::impl::random::uniform_size(
			sanguis::creator::impl::random::uniform_size::param_type::min(
				0u
			),
			sanguis::creator::impl::random::uniform_size::param_type::max(
				size.w() - 2
		)));

	sanguis::creator::impl::random::uniform_size_variate
	random_y(
		randgen,
		sanguis::creator::impl::random::uniform_size(
			sanguis::creator::impl::random::uniform_size::param_type::min(
				0u
			),
			sanguis::creator::impl::random::uniform_size::param_type::max(
				size.h() - 2
		)));

	// random starting position for maze generation,
	// has to be on tiles that satisfy
	// x % 2 == 1 && y % 2 == 1
	sanguis::creator::pos starting_pos(
		(random_x() / 2) * 2 + 1,
		(random_y() / 2) * 2 + 1
	);

	raw_maze
	[
		starting_pos
	] =
		sanguis::creator::impl::reachable(
			true);

	// wall tiles that are to be processed next
	std::vector<
		sanguis::creator::pos
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
				raw_maze,
				random_wall
			)
		};

		if(
			opposing_cell
		)
		{
			raw_maze[
				random_wall
			] =
				sanguis::creator::impl::reachable(true);

			raw_maze[
				*opposing_cell
			] =
				sanguis::creator::impl::reachable(true);

			// this actually appends some cells that aren't walls,
			// but they get filtered away the next time, since they
			// have two empty neighbors
			fcppt::algorithm::append(
				walls,
				fcppt::container::grid::neumann_neighbors(
					*opposing_cell
				)
			);
		}

		fcppt::algorithm::remove(
			walls,
			random_wall
		);
	}

	typedef
	sanguis::creator::grid::dim
	dim_type;

	dim_type const real_size(
		(
			raw_maze.size()
			-
			dim_type(
				1u,
				1u)
		)
		/
		2u
	);

	dim_type const result_size(
		real_size
		*
		spacing +
		(
			real_size
			+
			dim_type(
				1u,
				1u)
		)
		* wall_thickness
	);

	auto const coordinate_transform =
		[
			wall_thickness,
			spacing
		](dim_type::value_type a)
		{
			return
				(a / 2) * spacing
				+
				((a + 1) / 2) * wall_thickness;
		};

	auto const wall_or_space =
		[
			wall_thickness,
			spacing
		](dim_type::value_type a)
		{
			return
			a % 2 == 0
			?
			wall_thickness
			:
			spacing;
		};

	sanguis::creator::grid result{
		sanguis::creator::grid::dim(
			result_size)};

	for(
		auto cell :
		fcppt::container::grid::make_pos_crange(
			raw_maze)
	)
	{
		sanguis::creator::grid::pos const start(
			coordinate_transform(cell.pos().x()),
			coordinate_transform(cell.pos().y()));

		dim_type const cell_size(
			wall_or_space(cell.pos().x()),
			wall_or_space(cell.pos().y()));

		for(
			dim_type::value_type y = 0u;
			y < cell_size.h();
			++y
		)
			for(
				dim_type::value_type x = 0u;
				x < cell_size.w();
				++x
			)
				result
				[
					start
					+
					dim_type(
						x,
						y
					)
				] =
				(
					cell.value() ==
					sanguis::creator::impl::reachable(true)
					?
					empty
					:
					wall
				);
	}

	return result;
}
