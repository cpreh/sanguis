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
#include <fcppt/container/grid/make_pos_crange.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/dim/output.hpp>
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

auto
tile_is_nonsolid =
	[]
	(
		sanguis::creator::tile tile
	)
	{
		return
			!sanguis::creator::tile_is_solid(
				tile);
	};

sanguis::creator::opening_container
place_openings(
	sanguis::creator::grid const &,
	sanguis::creator::grid::pos const,
	sanguis::creator::opening_count const,
	::variate &,
	::variate &
);

sanguis::creator::spawn_container
place_spawners(
	sanguis::creator::grid &,
	unsigned const,
	sanguis::creator::aux_::randgen &
);

sanguis::creator::grid
generate_maze(
	sanguis::creator::grid::dim const &,
	unsigned const,
	unsigned const,
	sanguis::creator::tile const,
	sanguis::creator::tile const,
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
	auto const
	maze_dim =
		sanguis::creator::grid::dim(
			15,
			15);

	::variate
	random_cell_index(
		_parameters.randgen(),
		uniform_int(
			uniform_int::param_type::min(
				0u
			),
			uniform_int::param_type::max(
				maze_dim.w() *
				maze_dim.h()
			)));

	::variate
	random_x(
		_parameters.randgen(),
		uniform_int(
			uniform_int::param_type::min(
				0u
			),
			uniform_int::param_type::max(
				maze_dim.w() - 2
		)));

	::variate
	random_y(
		_parameters.randgen(),
		uniform_int(
			uniform_int::param_type::min(
				0u
			),
			uniform_int::param_type::max(
				maze_dim.h() - 2
		)));

	sanguis::creator::grid
	grid =
		generate_maze(
			maze_dim,
			2u,
			5u,
			sanguis::creator::tile::nothing,
			sanguis::creator::tile::concrete_wall,
			_parameters.randgen()
		);

	sanguis::creator::pos starting_pos =
		*sanguis::creator::aux_::find_closest(
			grid,
			sanguis::creator::pos(
				random_x(),
				random_y()
			),
			[](sanguis::creator::tile tile){
				return tile == sanguis::creator::tile::nothing;
			},
			10u);

	sanguis::creator::opening_container
	openings =
		::place_openings(
			grid,
			starting_pos,
			_parameters.opening_count(),
			random_x,
			random_y
		);

	for(
		auto &opening :
		openings
	)
		grid
		[
			opening.get()
		] =
			sanguis::creator::tile::door;

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

	sanguis::creator::background_grid grid_bg(
		grid.size(),
		sanguis::creator::background_tile::grass
	);

	sanguis::creator::spawn_container
	spawners =
		::place_spawners(
			grid,
			5u,
			_parameters.randgen()
		);

	return
		sanguis::creator::aux_::result(
			grid,
			grid_bg,
			openings,
			spawners
		);
}

namespace
{

sanguis::creator::opening_container
place_openings(
	sanguis::creator::grid const &grid,
	sanguis::creator::grid::pos const starting_pos,
	sanguis::creator::opening_count const opening_count,
	::variate &random_x,
	::variate &random_y
)
{
	sanguis::creator::opening_container
	result;

	// entrance
	result.push_back(
		sanguis::creator::opening(
			starting_pos));

	// exit
	auto
	closest_free =
		[
			&grid
		]
		(
			sanguis::creator::grid::pos const &pos
		)
		{
			return
			sanguis::creator::aux_::find_closest(
				grid,
				pos,
				[](sanguis::creator::tile tile){
					return tile == sanguis::creator::tile::nothing;
				},
				10u);
		};

	auto
	possible_opening =
		closest_free(
			sanguis::creator::grid::pos(
				(starting_pos.x() + grid.size().w() / 2) % grid.size().w(),
				(starting_pos.y() + grid.size().h() / 2) % grid.size().h()));

	FCPPT_ASSERT_ERROR_MESSAGE(
		possible_opening,
		FCPPT_TEXT(
			"Could not find a free tile close enough to the exit!"));

	result.push_back(
		sanguis::creator::opening(
			*possible_opening));

	// all remaining result
	auto
	current_results =
		result.size();

	unsigned iterations = 0;

	while(
		current_results <
		opening_count.get()
	)
	{
		if(
			++iterations
			>
			opening_count.get() * 5
		)
			throw sge::exception(
				FCPPT_TEXT(
					"Could not place opening, giving up."));

		auto
		candidate =
			closest_free(
				sanguis::creator::grid::pos(
						random_x(),
						random_y()));

		if (!candidate)
			continue;

		sanguis::creator::opening
		next_opening =
			sanguis::creator::opening(
				*candidate);

		if (
			!fcppt::algorithm::contains(
				result,
				next_opening)
		)
		{
			result.push_back(
				next_opening);

			++current_results;
		}
	}

	return result;
}

sanguis::creator::spawn_container
place_spawners(
	sanguis::creator::grid &grid,
	unsigned const spawner_count,
	sanguis::creator::aux_::randgen &randgen
)
{
	::variate random_x(
		randgen,
		uniform_int(
			uniform_int::param_type::min(
				1u
			),
			uniform_int::param_type::max(
				grid.size().w() - 2
		)));

	::variate random_y(
		randgen,
		uniform_int(
			uniform_int::param_type::min(
				1u
			),
			uniform_int::param_type::max(
				grid.size().h() - 2
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
		randgen,
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
			&grid
		]
		(
			sanguis::creator::grid::pos const &pos
		)
		{
			return
			sanguis::creator::aux_::find_closest(
				grid,
				pos,
				::tile_is_nonsolid,
				10u);
		};

	unsigned iterations = 0;

	while(
		current_spawners <
		spawner_count
	)
	{
		if(
			++iterations
			>
			spawner_count * 5
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

		grid
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

sanguis::creator::grid
generate_maze(
	sanguis::creator::grid::dim const &size,
	unsigned const wall_thickness,
	unsigned const spacing,
	sanguis::creator::tile const empty,
	sanguis::creator::tile const wall,
	sanguis::creator::aux_::randgen &randgen
)
{

	sanguis::creator::aux_::reachable_grid
	raw_maze(
		size,
		sanguis::creator::aux_::reachable(
			false)
	);

	::variate
	random_index(
		randgen,
		uniform_int(
			uniform_int::param_type::min(
				0u
			),
			uniform_int::param_type::max(
				std::numeric_limits<unsigned>::max()
		)));

	::variate
	random_x(
		randgen,
		uniform_int(
			uniform_int::param_type::min(
				0u
			),
			uniform_int::param_type::max(
				size.w() - 2
		)));

	::variate
	random_y(
		randgen,
		uniform_int(
			uniform_int::param_type::min(
				0u
			),
			uniform_int::param_type::max(
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
		sanguis::creator::aux_::reachable(
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

		fcppt::optional<
			sanguis::creator::pos
		>
		opposing_cell(
			sanguis::creator::aux_::find_opposing_cell(
				raw_maze,
				random_wall));

		if(
			opposing_cell
		)
		{
			raw_maze[
				random_wall
			] =
				sanguis::creator::aux_::reachable(true);

			raw_maze[
				*opposing_cell
			] =
				sanguis::creator::aux_::reachable(true);

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
					sanguis::creator::aux_::reachable(true)
					?
					empty
					:
					wall
				);
	}

	return result;
}

}
