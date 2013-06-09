#include <sanguis/creator/maze.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/parameters.hpp>
#include <sanguis/creator/result.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux/neumann_neighbors.hpp>
#include <sanguis/creator/aux/find_opposing_cell.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/remove.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/math/dim/output.hpp>
#include <sanguis/creator/randgen.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>


// this is a maze generator that follows the algorithm described at
// http://en.wikipedia.org/w/index.php?title=Maze_generation_algorithm&oldid=550777074#Randomized_Prim.27s_algorithm
sanguis::creator::result
sanguis::creator::maze(
	sanguis::creator::parameters const &_parameters
)
{
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			double
		>
	> uniform_real;

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			std::size_t
		>
	> uniform_int;

	uniform_real distribution(
		uniform_real::param_type::min(
			0.0
		),
		uniform_real::param_type::sup(
			1.0
		)
	);

	sanguis::creator::grid ret(
		sanguis::creator::grid::dim(
			_parameters.size().w(),
			_parameters.size().h()
		),
		sanguis::creator::tile::concrete_wall
	);

	uniform_int int_distribution(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
				ret.size().w() *
				ret.size().h()
		)
	);

	uniform_int w_dist(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			ret.size().w() - 2
		)
	);

	uniform_int h_dist(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			ret.size().h() - 2
		)
	);

	// random starting position for maze generation,
	// has to be on tiles that satisfy
	// x % 2 == 1 && y % 2 == 1
	sanguis::creator::grid::pos starting_pos(
		(w_dist(_parameters.randgen()) / 2) * 2 + 1,
		(h_dist(_parameters.randgen()) / 2) * 2 + 1
	);

	// add entry and exit points to the maze,
	// which obviously have to lie on the perimeter,
	// hard-coded for now.
	// TODO: add parameters for these
	ret[
		sanguis::creator::grid::pos(
			1,
			0
		)] =
		sanguis::creator::tile::nothing;

	ret[
		sanguis::creator::grid::pos(
			ret.size().w() - 1,
			ret.size().h() - 2
		)] =
		sanguis::creator::tile::nothing;

	// initialize grid with empty cells every other row and column,
	// surrounded on all sides by walls
	for (
		auto cell :
		fcppt::container::grid::make_pos_range(
			ret)
	)
	{
		if (
			cell.pos().x() % 2 == 1
			&&
			cell.pos().y() % 2 == 1
		)
			cell.value() =
				sanguis::creator::tile::nothing;
	}

	// wall tiles that are to be processed next
	std::vector<
		sanguis::creator::grid::pos
	> walls;

	// cells that were initially empty (and remain so) and
	// are marked as being part of the maze.
	std::vector<
		sanguis::creator::grid::pos
	> maze;

	// initially populate the set of walls with the neighbors
	// of the starting point
	for (
		auto &pos :
		sanguis::creator::aux::neumann_neighbors(
			starting_pos)
	)
	{
		if (
			ret
			[
				pos
			]
			==
				sanguis::creator::tile::concrete_wall
		)
		{
			walls.push_back(
				pos
			);
		}
	}

	// this follows the algorithm described at
	while (!walls.empty())
	{
		sanguis::creator::grid::pos const
		random_wall =
			walls[
				int_distribution(
					_parameters.randgen()
				) %
				walls.size()
			];

		fcppt::optional<
			sanguis::creator::grid::pos
		>
		opposing_cell =
			sanguis::creator::aux::find_opposing_cell(
				ret,
				maze,
				random_wall);

		if(
			opposing_cell
		)
		{
			ret[
				random_wall
			] =
				sanguis::creator::tile::nothing;

			ret[
				*opposing_cell
			] =
				sanguis::creator::tile::nothing;

			maze.push_back(
				*opposing_cell
			);

			fcppt::algorithm::append(
				walls,
				sanguis::creator::aux::neumann_neighbors(
					*opposing_cell
				)
			);
		}
		fcppt::algorithm::remove(
			walls,
			random_wall
		);
	}

	return
		sanguis::creator::result(
			ret,
			sanguis::creator::seed(
				0u
			),
			sanguis::creator::name(
				FCPPT_TEXT("maze")
			)
		);
}
