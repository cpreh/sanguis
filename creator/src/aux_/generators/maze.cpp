#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/enemy_type.hpp>
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
#include <sanguis/creator/aux_/find_opposing_cell.hpp>
#include <sanguis/creator/aux_/neighbor_array.hpp>
#include <sanguis/creator/aux_/neumann_neighbors.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/randgen.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <sanguis/creator/aux_/filled_rect.hpp>
#include <sanguis/creator/aux_/rect.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <sanguis/creator/aux_/generators/maze.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/algorithm/remove.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <ostream>
#include <fcppt/config/external_end.hpp>

// this is a maze generator that follows the algorithm described at
// http://en.wikipedia.org/w/index.php?title=Maze_generation_algorithm&oldid=550777074#Randomized_Prim.27s_algorithm
sanguis::creator::aux_::result
sanguis::creator::aux_::generators::maze(
	sanguis::creator::aux_::parameters const &_parameters
)
{
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::size_type
		>
	> uniform_int;

	sanguis::creator::grid grid(
		sanguis::creator::grid::dim(
			21,
			21
		),
		sanguis::creator::tile::concrete_wall
	);

	uniform_int int_distribution(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			grid.size().w() *
			grid.size().h()
		)
	);

	uniform_int w_dist(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			grid.size().w() - 2
		)
	);

	uniform_int h_dist(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			grid.size().h() - 2
		)
	);

	//openings begin

	auto clamp_to_grid =
		[]
		(
			long unsigned x,
			long unsigned max
		)
		{
			// max - 2 is the width or height of the effective grid (i.e. no borders)
			// the / 2 * 2 + 1 part forces an uneven result, which is an empty cell
			return (x % (max - 2)) / 2 * 2 + 1;
		};

	sanguis::creator::opening_container openings;

	std::size_t const opening_count =
		_parameters.opening_count().get();

	// random starting position for maze generation,
	// has to be on tiles that satisfy
	// x % 2 == 1 && y % 2 == 1
	sanguis::creator::grid::pos starting_pos(
		(w_dist(_parameters.randgen()) / 2) * 2 + 1,
		(h_dist(_parameters.randgen()) / 2) * 2 + 1
	);

	// entrance
	openings.push_back(
		sanguis::creator::opening(
			starting_pos));

	// exit
	openings.push_back(
		sanguis::creator::opening(
			sanguis::creator::grid::pos(
				clamp_to_grid(
					starting_pos.x() + grid.size().w() / 2,
					grid.size().w()),
				clamp_to_grid(
					starting_pos.y() + grid.size().h() / 2,
					grid.size().h())
	)));

	// all remaining openings
	auto current_openings =
		openings.size();

	while(
		current_openings <
		opening_count
	)
	{
		sanguis::creator::opening next_opening(
			sanguis::creator::grid::pos::null());

		next_opening =
			sanguis::creator::opening(
				sanguis::creator::grid::pos(
					clamp_to_grid(
						w_dist(_parameters.randgen()),
						grid.size().w()),
					clamp_to_grid(
						h_dist(_parameters.randgen()),
						grid.size().h())
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

	// openings end

	// initialize grid with empty cells every other row and column,
	// surrounded on all sides by walls
	for (
		auto cell :
		fcppt::container::grid::make_pos_range(
			grid)
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
		sanguis::creator::aux_::neumann_neighbors(
			starting_pos)
	)
	{
		if (
			grid
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
			sanguis::creator::aux_::find_opposing_cell(
				grid,
				maze,
				random_wall);

		if(
			opposing_cell
		)
		{
			grid[
				random_wall
			] =
				sanguis::creator::tile::nothing;

			grid[
				*opposing_cell
			] =
				sanguis::creator::tile::nothing;

			maze.push_back(
				*opposing_cell
			);

			fcppt::algorithm::append(
				walls,
				sanguis::creator::aux_::neumann_neighbors(
					*opposing_cell
				)
			);
		}
		fcppt::algorithm::remove(
			walls,
			random_wall
		);
	}

	sanguis::creator::grid::pos::value_type const
	scaling_factor = 2;

	// 1 in 6 chance...
	uniform_int fill_tile_random(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
			5u
		)
	);

	sanguis::creator::grid ret(
		grid.size() *
		scaling_factor,
		sanguis::creator::tile::nothing
	);

	sanguis::creator::background_grid ret_bg(
		ret.size(),
		sanguis::creator::background_tile::grass
	);

	for (
		auto cell :
		fcppt::container::grid::make_pos_range(
			grid)
	)
	{
		auto value = cell.value();

		for (auto dy = 0u; dy < scaling_factor; ++dy)
			for (auto dx = 0u; dx < scaling_factor; ++dx)
				if (
					fill_tile_random(
						_parameters.randgen()) !=
					0
				)
					ret[
						cell.pos() *
						scaling_factor +
						sanguis::creator::grid::pos(
							dx,
							dy)
					] = value;
	}

	// randomly create an asphalty area in the map
	sanguis::creator::aux_::filled_rect(
			sanguis::creator::pos(
				(w_dist(_parameters.randgen()) / 2u) * 2u + 1u,
				(h_dist(_parameters.randgen()) / 2u) * 2u + 1u
			) *
				scaling_factor,
				
			sanguis::creator::pos(
				(w_dist(_parameters.randgen()) / 2u) * 2u + 1u,
				(h_dist(_parameters.randgen()) / 2u) * 2u + 1u
			) *
				scaling_factor,
			[
				&ret,
				&ret_bg
			](
				sanguis::creator::pos pos
			)
			{
				auto p =
					fcppt::math::vector::structure_cast<
						sanguis::creator::pos
					>(
						pos);

				if (fcppt::container::grid::in_range(ret, p))
					ret_bg[p] = sanguis::creator::background_tile::asphalt;
			}
	);

	// fill the outer perimeter with walls
	sanguis::creator::aux_::rect(
			sanguis::creator::pos(
				0,
				0),
			sanguis::creator::pos(
				ret.size().w() - 1,
				ret.size().h() - 1),
			[&ret](
				sanguis::creator::pos pos
			)
			{
				if (fcppt::container::grid::in_range(ret, pos))
					ret[pos] = sanguis::creator::tile::concrete_wall;
			}
	);

	// scale the openings and set the appropriate tile
	for(
		auto &opening
		:
		openings
	)
	{
		opening = sanguis::creator::opening(
			opening.get() *
			scaling_factor
		);

		ret[
			opening.get()
		] =
			sanguis::creator::tile::door;
	}

	return
		sanguis::creator::aux_::result(
			ret,
			ret_bg,
			openings,
			sanguis::creator::spawn_container{
				sanguis::creator::spawn(
					sanguis::creator::spawn_pos(
						scaling_factor *
						sanguis::creator::pos(
							clamp_to_grid(
								w_dist(_parameters.randgen()),
								grid.size().w()),
							clamp_to_grid(
								h_dist(_parameters.randgen()),
								grid.size().h())
						)),
					sanguis::creator::enemy_type::maggot,
					sanguis::creator::spawn_type::spawner
				)
			}
		);
}
