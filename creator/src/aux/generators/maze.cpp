#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux/find_opposing_cell.hpp>
#include <sanguis/creator/aux/neighbor_array.hpp>
#include <sanguis/creator/aux/neumann_neighbors.hpp>
#include <sanguis/creator/aux/parameters.hpp>
#include <sanguis/creator/aux/randgen.hpp>
#include <sanguis/creator/aux/result.hpp>
#include <sanguis/creator/aux/generators/maze.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/algorithm/remove.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace
{

/**
 * Coordinates of a point on the perimeter of a rectangle ((0,0),(w,h)),
 * excluding the corners.
 * The order of traversal is as follows. Example: (w = 4, h = 3)
 * x 0 1 x
 * 5     2
 * x 4 3 x
 */
sanguis::creator::grid::pos
perimeter_to_coords(
	sanguis::creator::grid::dim const &,
	unsigned const &);

}

// this is a maze generator that follows the algorithm described at
// http://en.wikipedia.org/w/index.php?title=Maze_generation_algorithm&oldid=550777074#Randomized_Prim.27s_algorithm
sanguis::creator::aux::result
sanguis::creator::aux::generators::maze(
	sanguis::creator::aux::parameters const &_parameters
)
{
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::size_type
		>
	> uniform_int;

	sanguis::creator::grid ret(
		sanguis::creator::grid::dim(
			31u,
			31u
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

	// add entry and exit points to the maze,
	// which obviously have to lie on the perimeter.
	sanguis::creator::opening_container openings;

	unsigned const perimeter_length =
		static_cast<unsigned>(
			2 * (ret.size().w() - 2) +
			2 * (ret.size().h() - 2));

	unsigned const opening_count =
		_parameters.opening_count().get();

	for (
		unsigned o = 0u;
		o < opening_count;
		o++
	)
	{
		unsigned const t =
			o * (perimeter_length / opening_count);
		auto coords = perimeter_to_coords(ret.size(), t);
		std::cerr << coords.x() << " " << coords.y() << std::endl;
		openings.push_back(
			sanguis::creator::opening(
				coords
				));
	}

	// random starting position for maze generation,
	// has to be on tiles that satisfy
	// x % 2 == 1 && y % 2 == 1
	sanguis::creator::grid::pos starting_pos(
		(w_dist(_parameters.randgen()) / 2) * 2 + 1,
		(h_dist(_parameters.randgen()) / 2) * 2 + 1
	);

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

	for(
		auto const opening
		:
		openings
	)
		ret[
			opening.get()
		]
		=
		sanguis::creator::tile::nothing;

	return
		sanguis::creator::aux::result(
			ret,
			openings
		);
}

namespace
{
sanguis::creator::grid::pos
perimeter_to_coords(
	sanguis::creator::grid::dim const &_dim,
	unsigned const &_t)
{
	unsigned w2 = static_cast<unsigned>(_dim.w() - 2);
	unsigned h2 = static_cast<unsigned>(_dim.h() - 2);

	FCPPT_ASSERT_ERROR(
		w2 > 0);

	FCPPT_ASSERT_ERROR(
		h2 > 0);

	FCPPT_ASSERT_ERROR(
		_t < 2 * w2 + 2 * h2);

	if (_t < w2)
		return sanguis::creator::grid::pos(
			_t + 1,
			0);

	if (_t < w2 + h2)
		return sanguis::creator::grid::pos(
			w2 + 1,
			_t - w2 + 1);

	if (_t < 2 * w2 + h2)
		return sanguis::creator::grid::pos(
			w2 - (_t - w2 - h2),
			h2 + 1);

	return sanguis::creator::grid::pos(
		0,
		h2 - (_t - 2 * w2 - h2));
}
}
