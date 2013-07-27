#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/spawn_pos.hpp>
#include <sanguis/creator/spawn_type.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux/find_opposing_cell.hpp>
#include <sanguis/creator/aux/neighbor_array.hpp>
#include <sanguis/creator/aux/neumann_neighbors.hpp>
#include <sanguis/creator/aux/parameters.hpp>
#include <sanguis/creator/aux/randgen.hpp>
#include <sanguis/creator/aux/result.hpp>
#include <sanguis/creator/aux/generators/maze.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/algorithm/remove.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/math/diff.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
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
			61u,
			61u
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

	sanguis::creator::opening_container openings;

	unsigned const opening_count =
		_parameters.opening_count().get();

	// random starting position for maze generation,
	// has to be on tiles that satisfy
	// x % 2 == 1 && y % 2 == 1
	sanguis::creator::grid::pos starting_pos(
		(w_dist(_parameters.randgen()) / 2) * 2 + 1,
		(h_dist(_parameters.randgen()) / 2) * 2 + 1
	);

	openings.push_back(
		sanguis::creator::opening(
			starting_pos));

	// should always be true, since there should be 2 or more openings
	if(
		openings.size() <
		opening_count
	)
	{
		sanguis::creator::grid::pos exit_opening(
			sanguis::creator::grid::pos::null());

		unsigned distance;

		unsigned const min_distance =
			std::min(
				ret.size().h(),
				ret.size().w()
			) /
			2;

		do
		{
			exit_opening =
				sanguis::creator::grid::pos(
					(w_dist(_parameters.randgen()) / 2) * 2 + 1,
					(h_dist(_parameters.randgen()) / 2) * 2 + 1
				);
			distance =
				[](
					sanguis::creator::grid::pos a,
					sanguis::creator::grid::pos b)
				{
					return
						fcppt::math::diff(a.x(), b.x())
						+
						fcppt::math::diff(a.y(), b.y());
				}
				(
						exit_opening,
						starting_pos
				);

			if (distance < min_distance)
				fcppt::io::cerr()
					<< FCPPT_TEXT("openings too close (")
					<< distance
					<< FCPPT_TEXT("), retrying...")
					<< std::endl;
		}
		while(
				distance
			<
				min_distance
		);

		openings.push_back(
			sanguis::creator::opening(
				exit_opening));
	}

	unsigned current_openings =
		openings.size();

	while (
		current_openings <
		opening_count
	)
	{
		sanguis::creator::opening next_opening(
			sanguis::creator::grid::pos(
				(w_dist(_parameters.randgen()) / 2) * 2 + 1,
				(h_dist(_parameters.randgen()) / 2) * 2 + 1
		));

		if (
			!fcppt::algorithm::contains(
				openings,
				next_opening)
		)
		{
			openings.push_back(
				next_opening);
			current_openings++;
		}
	}

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
		sanguis::creator::tile::door;

	return
		sanguis::creator::aux::result(
			ret,
			sanguis::creator::background_grid(
				ret.size(),
				sanguis::creator::background_tile::nothing
			),
			openings,
			sanguis::creator::spawn_container{
				sanguis::creator::spawn(
					sanguis::creator::spawn_pos(
						sanguis::creator::pos(
							5,
							5
						)
					),
					sanguis::creator::spawn_type::test
				)
			}
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
