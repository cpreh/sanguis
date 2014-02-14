#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux_/enemy_type_container.hpp>
#include <sanguis/creator/aux_/generate_maze.hpp>
#include <sanguis/creator/aux_/place_openings.hpp>
#include <sanguis/creator/aux_/place_spawners.hpp>
#include <sanguis/creator/aux_/parameters.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <sanguis/creator/aux_/random/generator.hpp>
#include <sanguis/creator/aux_/random/uniform_int.hpp>
#include <sanguis/creator/aux_/random/uniform_size.hpp>
#include <sanguis/creator/aux_/random/uniform_size_variate.hpp>
#include <sanguis/creator/aux_/generators/graveyard.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/transform/enum.hpp>


sanguis::creator::aux_::result
sanguis::creator::aux_::generators::graveyard(
	sanguis::creator::aux_::parameters const &_parameters
)
{
	sanguis::creator::grid::dim const maze_dim{
		9,
		9
	};

	sanguis::creator::aux_::random::uniform_size_variate
	random_cell_index{
		_parameters.randgen(),
		sanguis::creator::aux_::random::uniform_size{
			sanguis::creator::aux_::random::uniform_size::param_type::min{
				0u
			},
			sanguis::creator::aux_::random::uniform_size::param_type::max{
				maze_dim.content()
			}
		}
	};

	sanguis::creator::aux_::random::uniform_size_variate
	random_x{
		_parameters.randgen(),
		sanguis::creator::aux_::random::uniform_size{
			sanguis::creator::aux_::random::uniform_size::param_type::min{
				0u
			},
			sanguis::creator::aux_::random::uniform_size::param_type::max{
				maze_dim.w() - 2
			}
		}
	};

	sanguis::creator::aux_::random::uniform_size_variate
	random_y{
		_parameters.randgen(),
		sanguis::creator::aux_::random::uniform_size{
			sanguis::creator::aux_::random::uniform_size::param_type::min{
				0u
			},
			sanguis::creator::aux_::random::uniform_size::param_type::max{
				maze_dim.h() - 2
			}
		}
	};

	sanguis::creator::grid
	grid{
		sanguis::creator::aux_::generate_maze(
			maze_dim,
			1u,
			5u,
			sanguis::creator::tile::nothing,
			sanguis::creator::tile::hedge,
			_parameters.randgen()
		)
	};

	sanguis::creator::opening_container
	openings{
		sanguis::creator::aux_::place_openings(
			grid,
			_parameters.opening_count(),
			random_x,
			random_y
		)
	};

	typedef
	fcppt::random::distribution::basic<
		sanguis::creator::aux_::random::uniform_int<
			unsigned
		>
	>
	uniform_int2;

	auto fill_tile_random(
		fcppt::random::make_variate(
			_parameters.randgen(),
			uniform_int2{
				uniform_int2::param_type::min{
					0u
				},
				uniform_int2::param_type::max{
					10u
				}
			}
		)
	);

	typedef
	fcppt::random::distribution::basic<
		sanguis::creator::aux_::random::uniform_int<
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
		auto cell
		:
		fcppt::container::grid::make_pos_range(
			grid
		)
	)
	{
		if(
			cell.value()
			==
			sanguis::creator::tile::nothing
			&&
			fill_tile_random()
			== 0
		)
			cell.value() =
				random_grave();
	}

	sanguis::creator::background_grid const grid_bg{
		grid.size(),
		sanguis::creator::background_tile::grass
	};

	sanguis::creator::spawn_container const
	spawners{
		sanguis::creator::aux_::place_spawners(
			grid,
			10u,
			_parameters.randgen(),
			sanguis::creator::aux_::enemy_type_container{
				sanguis::creator::enemy_type::zombie00,
				sanguis::creator::enemy_type::zombie01,
				sanguis::creator::enemy_type::skeleton,
				sanguis::creator::enemy_type::ghost
			}
		)
	};

	return
		sanguis::creator::aux_::result(
			grid,
			grid_bg,
			openings,
			spawners
		);
}
