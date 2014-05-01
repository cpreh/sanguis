#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/background_tile.hpp>
#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/destructible_pos.hpp>
#include <sanguis/creator/destructible_type.hpp>
#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux_/parameters_fwd.hpp>
#include <sanguis/creator/aux_/result.hpp>
#include <sanguis/creator/aux_/generators/start.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/grid/make_pos_range_start_end.hpp>


sanguis::creator::aux_::result
sanguis::creator::aux_::generators::start(
	sanguis::creator::aux_::parameters const &
)
{
	sanguis::creator::dim const grid_size{
		10,
		10
	};

	sanguis::creator::grid grid{
		grid_size,
		sanguis::creator::tile::concrete_wall
	};

	for(
		auto const pos
		:
		fcppt::container::grid::make_pos_range_start_end(
			grid,
			sanguis::creator::pos(
				1,
				1
			),
			sanguis::creator::pos(
				grid_size.w() - 1u,
				grid_size.h() - 1u
			)
		)
	)
		pos.value() =
			sanguis::creator::tile::nothing;

	sanguis::creator::opening const start_portal{
		sanguis::creator::pos{
			1,
			grid_size.h()
			/
			2
		}
	};

	sanguis::creator::opening const exit_portal{
		sanguis::creator::pos{
			grid_size.w()
			-
			2,
			grid_size.h()
			/
			2
		}
	};

	grid[
		exit_portal.get()
	] =
		sanguis::creator::tile::door;

	return
		sanguis::creator::aux_::result{
			grid,
			sanguis::creator::background_grid{
				grid_size,
				sanguis::creator::background_tile::grass
			},
			sanguis::creator::opening_container{
				start_portal,
				exit_portal
			},
			sanguis::creator::spawn_container(),
			sanguis::creator::destructible_container{
				// TODO: Just for testing
				sanguis::creator::destructible(
					sanguis::creator::destructible_pos(
						sanguis::creator::pos(
							2,
							2
						)
					),
					sanguis::creator::destructible_type::barrel
				)
			}
		};
}
