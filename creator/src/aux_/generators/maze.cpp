#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux_/enemy_type_container.hpp>
#include <sanguis/creator/aux_/generate_maze.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/place_destructibles.hpp>
#include <sanguis/creator/aux_/place_openings.hpp>
#include <sanguis/creator/aux_/place_spawners.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <sanguis/creator/aux_/generators/maze.hpp>


sanguis::creator::aux_::result
sanguis::creator::aux_::generators::maze(
	sanguis::creator::aux_::parameters const &_parameters
)
{
	sanguis::creator::grid::dim const maze_dim{
		15,
		15
	};

	sanguis::creator::grid
	grid{
		sanguis::creator::aux_::generate_maze(
			maze_dim,
			1u,
			2u,
			sanguis::creator::tile::nothing,
			sanguis::creator::tile::concrete_wall,
			_parameters.randgen()
		)
	};

	sanguis::creator::opening_container const
	openings{
		sanguis::creator::aux_::place_openings(
			grid,
			_parameters.randgen(),
			_parameters.opening_count()
		)
	};

	sanguis::creator::spawn_container const
	spawners{
		sanguis::creator::aux_::place_spawners(
			grid,
			openings,
			20u,
			_parameters.randgen(),
			sanguis::creator::aux_::enemy_type_container{
				sanguis::creator::enemy_type::wolf_black,
				sanguis::creator::enemy_type::wolf_brown,
				sanguis::creator::enemy_type::wolf_white,
				sanguis::creator::enemy_type::zombie00,
				sanguis::creator::enemy_type::zombie01,
				sanguis::creator::enemy_type::spider,
				sanguis::creator::enemy_type::skeleton,
				sanguis::creator::enemy_type::ghost,
				sanguis::creator::enemy_type::maggot
			}
		)
	};

	sanguis::creator::destructible_container const
	destructibles{
		sanguis::creator::aux_::place_destructibles(
			grid,
			_parameters.randgen()
		)
	};

	sanguis::creator::background_grid const grid_bg(
		grid.size(),
		sanguis::creator::background_tile::asphalt
	);

	return
		sanguis::creator::aux_::result(
			grid,
			grid_bg,
			openings,
			spawners,
			destructibles
		);
}
