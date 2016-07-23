#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/enemy_type_container.hpp>
#include <sanguis/creator/impl/generate_maze.hpp>
#include <sanguis/creator/impl/interior_range.hpp>
#include <sanguis/creator/impl/maze_to_tile_grid.hpp>
#include <sanguis/creator/impl/parameters.hpp>
#include <sanguis/creator/impl/place_openings.hpp>
#include <sanguis/creator/impl/place_spawners.hpp>
#include <sanguis/creator/impl/reachable.hpp>
#include <sanguis/creator/impl/reachable_grid.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <sanguis/creator/impl/generators/graveyard.hpp>
#include <sanguis/creator/impl/random/generator.hpp>
#include <sanguis/creator/impl/random/uniform_int.hpp>
#include <fcppt/container/grid/make_pos_ref_range.hpp>
#include <fcppt/random/make_variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/type_iso/enum.hpp>


sanguis::creator::impl::result
sanguis::creator::impl::generators::graveyard(
	sanguis::creator::impl::parameters const &_parameters
)
{
	sanguis::creator::impl::reachable_grid
	initial_maze{
		sanguis::creator::grid::dim{
			9u,
			9u
		},
		sanguis::creator::impl::reachable(false)
	};

	sanguis::creator::impl::generate_maze(
		initial_maze,
		_parameters.randgen()
	);

	sanguis::creator::grid
	grid{
		sanguis::creator::impl::maze_to_tile_grid(
			initial_maze,
			1u,
			5u,
			sanguis::creator::tile::nothing,
			sanguis::creator::tile::hedge
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

	typedef
	fcppt::random::distribution::basic<
		sanguis::creator::impl::random::uniform_int<
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
		sanguis::creator::impl::random::uniform_int<
			sanguis::creator::tile
		>
	> uniform_tile_enum;

	sanguis::creator::background_grid grid_bg{
		grid.size(),
		sanguis::creator::background_tile::grass
	};

	auto random_dirt_grass(
		fcppt::random::make_variate(
			_parameters.randgen(),
			uniform_int2{
				uniform_int2::param_type::min{
					0u
				},
				uniform_int2::param_type::max{
					1u
				}
			}
		)
	);

	for(
		auto const pos
		:
		sanguis::creator::impl::interior_range(
			grid_bg
		)
	)
		pos.value() =
			random_dirt_grass()
			?
			sanguis::creator::background_tile::dirt
			:
			sanguis::creator::background_tile::grass;

	auto random_grave(
		fcppt::random::make_variate(
			_parameters.randgen(),
			uniform_tile_enum(
				uniform_tile_enum::param_type::min(
					sanguis::creator::tile::grave2
				),
				uniform_tile_enum::param_type::max(
					sanguis::creator::tile::grave5
				)
			)
		)
	);

	for(
		auto const cell
		:
		fcppt::container::grid::make_pos_ref_range(
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
			&&
			grid_bg[
				cell.pos()
			] ==
			sanguis::creator::background_tile::grass
		)
			cell.value() =
				random_grave();
	}

	sanguis::creator::spawn_container const
	spawners{
		sanguis::creator::impl::place_spawners(
			_parameters.log(),
			grid,
			openings,
			10u,
			_parameters.randgen(),
			sanguis::creator::impl::enemy_type_container{
				sanguis::creator::enemy_type::zombie00,
				sanguis::creator::enemy_type::zombie01,
				sanguis::creator::enemy_type::skeleton,
				sanguis::creator::enemy_type::ghost
			},
			_parameters.spawn_boss(),
			sanguis::creator::tile::grave1
		)
	};

	return
		sanguis::creator::impl::result(
			grid,
			grid_bg,
			openings,
			spawners,
			sanguis::creator::destructible_container() // TODO
		);
}
