#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/enemy_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/size_type.hpp>
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
#include <fcppt/make_ref.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::creator::impl::result
sanguis::creator::impl::generators::maze(
	sanguis::creator::impl::parameters const &_parameters
)
{
	constexpr sanguis::creator::size_type const side_length{
		15U
	};

	sanguis::creator::impl::reachable_grid initial_maze{
		sanguis::creator::impl::reachable_grid::dim(
			side_length,
			side_length
		),
		sanguis::creator::impl::reachable(false)
	};

	sanguis::creator::impl::filled_rect(
		sanguis::creator::rect{
			sanguis::creator::rect::vector{
				1U,
				1U
			},
			sanguis::creator::rect::dim{
				5U, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
				5U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
			}
		},
		[
			&initial_maze
		](
			sanguis::creator::pos const &_p
		){
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::container::grid::at_optional(
					initial_maze,
					_p
				)
			).get() =
				sanguis::creator::impl::reachable(true);
		}
	);

	sanguis::creator::impl::generate_maze(
		fcppt::make_ref(
			initial_maze
		),
		_parameters.randgen()
	);

	sanguis::creator::grid grid{
		sanguis::creator::impl::maze_to_tile_grid(
			initial_maze,
			1U,
			2U,
			sanguis::creator::tile::nothing,
			sanguis::creator::tile::concrete_wall
		)
	};

	sanguis::creator::opening_container_array openings(
		sanguis::creator::impl::place_openings(
			fcppt::make_ref(
				grid
			),
			_parameters.randgen(),
			_parameters.opening_count_array()
		)
	);

	sanguis::creator::spawn_container spawners{
		sanguis::creator::impl::place_spawners(
			_parameters.log(),
			fcppt::make_ref(
				grid
			),
			openings,
			20U, // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
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
			_parameters.spawn_boss(),
			sanguis::creator::tile::spawner
		)
	};

	sanguis::creator::destructible_container destructibles{
		sanguis::creator::impl::place_destructibles(
			fcppt::make_ref(
				grid
			),
			_parameters.randgen()
		)
	};

	sanguis::creator::background_grid grid_bg(
		grid.size(),
		sanguis::creator::background_tile::asphalt
	);

	return
		sanguis::creator::impl::result(
			std::move(
				grid
			),
			std::move(
				grid_bg
			),
			std::move(
				openings
			),
			std::move(
				spawners
			),
			std::move(
				destructibles
			)
		);
}
