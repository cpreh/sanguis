#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/enemy_type_container.hpp>
#include <sanguis/creator/impl/filled_rect.hpp>
#include <sanguis/creator/impl/generate_maze.hpp>
#include <sanguis/creator/impl/maze_to_tile_grid.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/place_destructibles.hpp>
#include <sanguis/creator/impl/place_openings.hpp>
#include <sanguis/creator/impl/place_spawners.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <sanguis/creator/impl/generators/maze.hpp>


sanguis::creator::impl::result
sanguis::creator::impl::generators::maze(
	sanguis::creator::impl::parameters const &_parameters
)
{
	sanguis::creator::impl::reachable_grid initial_maze{
		sanguis::creator::impl::reachable_grid::dim(
			15u,
			15u
		),
		sanguis::creator::impl::reachable(false)
	};

	sanguis::creator::impl::filled_rect(
		sanguis::creator::rect{
			sanguis::creator::rect::vector{
				1u,
				1u
			},
			sanguis::creator::rect::dim{
				5u,
				5u
			}
		},
		[
			&initial_maze
		](
			sanguis::creator::pos const &_p
		){
			initial_maze[
				_p
			] =
				sanguis::creator::impl::reachable(true);
		}
	);

	sanguis::creator::impl::generate_maze(
		initial_maze,
		_parameters.randgen()
	);

	sanguis::creator::grid
	grid{
		sanguis::creator::impl::maze_to_tile_grid(
			initial_maze,
			1u,
			2u,
			sanguis::creator::tile::nothing,
			sanguis::creator::tile::concrete_wall
		)
	};

	sanguis::creator::opening_container_array const
	openings(
		sanguis::creator::impl::place_openings(
			grid,
			_parameters.randgen(),
			_parameters.opening_count_array()
		)
	);

	sanguis::creator::spawn_container const
	spawners{
		sanguis::creator::impl::place_spawners(
			grid,
			openings,
			20u,
			_parameters.randgen(),
			sanguis::creator::impl::enemy_type_container{
				sanguis::creator::enemy_type::wolf_black,
				sanguis::creator::enemy_type::wolf_brown,
				sanguis::creator::enemy_type::wolf_white,
				sanguis::creator::enemy_type::zombie00,
				sanguis::creator::enemy_type::zombie01,
				sanguis::creator::enemy_type::spider,
				sanguis::creator::enemy_type::skeleton,
				sanguis::creator::enemy_type::ghost,
				sanguis::creator::enemy_type::maggot
			},
			_parameters.spawn_boss()
		)
	};

	sanguis::creator::destructible_container const
	destructibles{
		sanguis::creator::impl::place_destructibles(
			grid,
			_parameters.randgen()
		)
	};

	sanguis::creator::background_grid const grid_bg(
		grid.size(),
		sanguis::creator::background_tile::asphalt
	);

	return
		sanguis::creator::impl::result(
			grid,
			grid_bg,
			openings,
			spawners,
			destructibles
		);
}
