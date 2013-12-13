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
#include <sanguis/creator/aux_/generate_maze.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/randgen.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <sanguis/creator/aux_/filled_rect.hpp>
#include <sanguis/creator/aux_/find_closest.hpp>
#include <sanguis/creator/aux_/rect.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <sanguis/creator/aux_/generators/graveyard.hpp>
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
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_indices.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/distribution/transform/enum.hpp>
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

}

// this is a maze generator that follows the algorithm described at
// http://en.wikipedia.org/w/index.php?title=Maze_generation_algorithm&oldid=550777074#Randomized_Prim.27s_algorithm
sanguis::creator::aux_::result
sanguis::creator::aux_::generators::graveyard(
	sanguis::creator::aux_::parameters const &_parameters
)
{
	auto const
	maze_dim =
		sanguis::creator::grid::dim(
			9,
			9);

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
		sanguis::creator::aux_::generate_maze(
			maze_dim,
			1u,
			5u,
			sanguis::creator::tile::nothing,
			sanguis::creator::tile::hedge,
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

	auto fill_tile_random(
		fcppt::random::make_variate(
			_parameters.randgen(),
			uniform_real(
				uniform_real::param_type::min(
					0.f
				),
				uniform_real::param_type::sup(
					1.0f
				)
			)
		)
	);

	typedef
	fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			sanguis::creator::tile
		>
	> uniform_tile_enum;

	auto random_grave(
		fcppt::random::make_variate(
			_parameters.randgen(),
			uniform_tile_enum(
				uniform_tile_enum::param_type::min(
					sanguis::creator::tile::grave1
				),
				uniform_tile_enum::param_type::max(
					sanguis::creator::tile::grave5
				)
			)
		)
	);

	for(
		auto cell :
		fcppt::container::grid::make_pos_range(
			grid)
	)
	{
		if(
			cell.value()
			==
			sanguis::creator::tile::nothing
			&&
			fill_tile_random()
			< 0.1f
		)
			cell.value() =
				random_grave();
	}

	sanguis::creator::background_grid grid_bg(
		grid.size(),
		sanguis::creator::background_tile::grass
	);

	sanguis::creator::spawn_container
	spawners =
		::place_spawners(
			grid,
			10u,
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

	auto const monsters = {
		sanguis::creator::enemy_type::zombie00,
		sanguis::creator::enemy_type::zombie01,
		sanguis::creator::enemy_type::skeleton,
		sanguis::creator::enemy_type::ghost
	};

	auto random_monster(
		fcppt::random::distribution::make_basic(
			fcppt::random::distribution::parameters::make_uniform_indices(
				monsters
			)
		)
	);

	sanguis::creator::spawn_container
	spawners;

	auto
	current_spawners =
		fcppt::literal<
			sanguis::creator::spawn_container::size_type
		>(
			0);

	auto
	closest_empty =
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
				[](sanguis::creator::tile _tile){
					return _tile == sanguis::creator::tile::nothing;
				},
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
			closest_empty(
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
					*candidate
				),
				// TODO: Simplify operator[] for initializer lists
				*(
					monsters.begin()
					+
					random_monster(
						randgen
					)
				),
				sanguis::creator::spawn_type::spawner
			)
		);

		current_spawners++;
	}

	return spawners;
}

}
