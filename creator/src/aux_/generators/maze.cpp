#include <sge/exception.hpp>
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
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/aux_/find_opposing_cell.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/randgen.hpp>
#include <sanguis/creator/aux_/reachable.hpp>
#include <sanguis/creator/aux_/reachable_grid.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <sanguis/creator/aux_/filled_rect.hpp>
#include <sanguis/creator/aux_/find_closest.hpp>
#include <sanguis/creator/aux_/rect.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <sanguis/creator/aux_/generators/maze.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/algorithm/remove.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_enum.hpp>
#include <fcppt/random/distribution/transform/enum.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace
{

typedef
fcppt::random::distribution::basic<
	fcppt::random::distribution::parameters::uniform_int<
		sanguis::creator::size_type
	>
>
uniform_int;

typedef fcppt::random::variate<
	sanguis::creator::aux_::randgen,
	uniform_int
> variate;

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

auto
tile_is_nonsolid =
	[](sanguis::creator::tile _tile){return !sanguis::creator::tile_is_solid(_tile);};

sanguis::creator::opening_container
openings(
	sanguis::creator::grid const &,
	sanguis::creator::grid::pos const,
	sanguis::creator::opening_count const,
	::variate &,
	::variate &
);

sanguis::creator::spawn_container
spawners(
	sanguis::creator::grid &,
	unsigned const,
	sanguis::creator::aux_::randgen &
);

}

// this is a maze generator that follows the algorithm described at
// http://en.wikipedia.org/w/index.php?title=Maze_generation_algorithm&oldid=550777074#Randomized_Prim.27s_algorithm
sanguis::creator::aux_::result
sanguis::creator::aux_::generators::maze(
	sanguis::creator::aux_::parameters const &_parameters
)
{
	// initialize grid with walls
	sanguis::creator::grid grid(
		sanguis::creator::grid::dim(
			21,
			21
		),
		sanguis::creator::tile::concrete_wall
	);

	::variate
	random_cell_index(
		_parameters.randgen(),
		uniform_int(
			uniform_int::param_type::min(
				0u
			),
			uniform_int::param_type::max(
				grid.size().w() *
				grid.size().h()
			)));

	::variate
	random_x(
		_parameters.randgen(),
		uniform_int(
			uniform_int::param_type::min(
				0u
			),
			uniform_int::param_type::max(
				grid.size().w() - 2
		)));

	::variate
	random_y(
		_parameters.randgen(),
		uniform_int(
			uniform_int::param_type::min(
				0u
			),
			uniform_int::param_type::max(
				grid.size().h() - 2
		)));

	// random starting position for maze generation,
	// has to be on tiles that satisfy
	// x % 2 == 1 && y % 2 == 1
	sanguis::creator::grid::pos starting_pos(
		(random_x() / 2) * 2 + 1,
		(random_y() / 2) * 2 + 1
	);

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
		fcppt::container::grid::neumann_neighbors(
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
				random_cell_index() %
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

	sanguis::creator::opening_container
	openings =
		::openings(
			grid,
			starting_pos,
			_parameters.opening_count(),
			random_x,
			random_y
		);

	sanguis::creator::grid::pos::value_type const
	scaling_factor = 2;

	typedef
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			float
		>
	>
	uniform_real;

	fcppt::random::variate<
		sanguis::creator::aux_::randgen,
		uniform_real
	>
	fill_tile_random(
		_parameters.randgen(),
		uniform_real(
			uniform_real::param_type::min(
				0.f
			),
			uniform_real::param_type::sup(
				1.0f
			)
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
					fill_tile_random() <
					.85f
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
				(random_x() / 2u) * 2u + 1u,
				(random_y() / 2u) * 2u + 1u
			) *
				scaling_factor,
				
			sanguis::creator::pos(
				(random_x() / 2u) * 2u + 1u,
				(random_y() / 2u) * 2u + 1u
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


	sanguis::creator::spawn_container
	spawners =
		::spawners(
			ret,
			// FIXME: depending on the difficulty?
			5u,
			_parameters.randgen()
		);

	return
		sanguis::creator::aux_::result(
			ret,
			ret_bg,
			openings,
			spawners
		);
}

namespace
{

sanguis::creator::opening_container
openings(
	sanguis::creator::grid const &_grid,
	sanguis::creator::grid::pos const _starting_pos,
	sanguis::creator::opening_count const _opening_count,
	::variate &_random_x,
	::variate &_random_y
)
{
	sanguis::creator::opening_container
	openings;

	// entrance
	openings.push_back(
		sanguis::creator::opening(
			_starting_pos));

	// exit
	auto
	closest_nonsolid =
		[
			&_grid
		]
		(
			sanguis::creator::grid::pos const &_pos
		)
		{
			return
			sanguis::creator::aux_::find_closest(
				_grid,
				_pos,
				::tile_is_nonsolid,
				10u);
		};

	auto
	possible_opening =
		closest_nonsolid(
			sanguis::creator::grid::pos(
				(_starting_pos.x() + _grid.size().w() / 2) % _grid.size().w(),
				(_starting_pos.y() + _grid.size().h() / 2) % _grid.size().h()));

	FCPPT_ASSERT_ERROR_MESSAGE(
		possible_opening,
		FCPPT_TEXT(
			"Could not find a nonsolid tile close enough to the intended exit!"));

	openings.push_back(
		sanguis::creator::opening(
			*possible_opening));

	// all remaining openings
	auto
	current_openings =
		openings.size();

	unsigned iterations = 0;

	while(
		current_openings <
		_opening_count.get()
	)
	{
		if(
			++iterations
			>
			_opening_count.get() * 5
		)
			throw sge::exception(
				FCPPT_TEXT(
					"Could not place openings, giving up."));

		auto
		candidate =
			closest_nonsolid(
				sanguis::creator::grid::pos(
						_random_x(),
						_random_y()));

		if (!candidate)
			continue;

		sanguis::creator::opening
		next_opening =
			sanguis::creator::opening(
				*candidate);

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

	return openings;
}

sanguis::creator::spawn_container
spawners(
	sanguis::creator::grid &_grid,
	unsigned const _spawner_count,
	sanguis::creator::aux_::randgen &_randgen
)
{
	::variate random_x(
		_randgen,
		uniform_int(
			uniform_int::param_type::min(
				1u
			),
			uniform_int::param_type::max(
				_grid.size().w() - 2
		)));

	::variate random_y(
		_randgen,
		uniform_int(
			uniform_int::param_type::min(
				1u
			),
			uniform_int::param_type::max(
				_grid.size().h() - 2
		)));

	typedef
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::enemy_type
		>
	> uniform_enum;

	typedef
	fcppt::random::variate<
		sanguis::creator::aux_::randgen,
		uniform_enum
	> random_monster_type;

	random_monster_type
	random_monster(
		_randgen,
		uniform_enum(
			fcppt::random::distribution::parameters::make_uniform_enum<
				sanguis::creator::enemy_type
			>()
		));

	sanguis::creator::spawn_container
	spawners;

	auto
	current_spawners =
		fcppt::literal<
			sanguis::creator::spawn_container::size_type
		>(
			0);

	auto
	closest_nonsolid =
		[
			&_grid
		]
		(
			sanguis::creator::grid::pos const &pos
		)
		{
			return
			sanguis::creator::aux_::find_closest(
				_grid,
				pos,
				::tile_is_nonsolid,
				5u);
		};

	unsigned iterations = 0;

	while(
		current_spawners <
		_spawner_count
	)
	{
		if(
			++iterations
			>
			_spawner_count * 5
		)
			throw sge::exception(
				FCPPT_TEXT(
					"Could not place spawners, giving up."));

		auto candidate =
			closest_nonsolid(
					sanguis::creator::grid::pos(
						random_x(),
						random_y()));

		if (!candidate)
			continue;

		_grid
		[
			*candidate
		] =
		sanguis::creator::tile::spawner;

		spawners.push_back(
			sanguis::creator::spawn(
				sanguis::creator::spawn_pos(
					*candidate),
				random_monster(),
				sanguis::creator::spawn_type::spawner));

		current_spawners++;
	}

	return spawners;
}

}
