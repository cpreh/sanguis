#include <sanguis/creator/aux_/enemy_type_container.hpp>
#include <sanguis/creator/aux_/generators/rooms.hpp>
#include <sanguis/creator/aux_/generate_rooms.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/place_spawners.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>

sanguis::creator::aux_::result
sanguis::creator::aux_::generators::rooms(
	sanguis::creator::aux_::parameters const &_parameters
)
{
	sanguis::creator::grid
	grid{
		sanguis::creator::aux_::generate_rooms(
			sanguis::creator::grid::dim{
				50u,
				30u
			},
			sanguis::creator::tile::concrete_wall,
			sanguis::creator::tile::nothing,
			_parameters.randgen()
		)
	};

	sanguis::creator::opening_container
	openings{
		sanguis::creator::opening{
			sanguis::creator::pos{2u,2u}
		},
		sanguis::creator::opening{
			sanguis::creator::pos{2u,3u}
		}
	};

	grid[
		sanguis::creator::pos{2u,2u}
	] = sanguis::creator::tile::door;
	grid[
		sanguis::creator::pos{2u,3u}
	] = sanguis::creator::tile::door;

	sanguis::creator::background_grid const bg_grid{
		grid.size(),
		sanguis::creator::background_tile::grass
	};

	sanguis::creator::spawn_container const
	spawners{
		/*
		sanguis::creator::aux_::place_spawners(
			grid,
			openings,
			10u,
			_parameters.randgen(),
			sanguis::creator::aux_::enemy_type_container{
				sanguis::creator::enemy_type::zombie00
			}
		)
		*/
	};

	return
		sanguis::creator::aux_::result(
			grid,
			bg_grid,
			openings,
			spawners,
			sanguis::creator::destructible_container{}
		);
}
