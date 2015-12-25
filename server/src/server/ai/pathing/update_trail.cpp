#include <sanguis/creator/optional_pos.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/pathing/optional_target.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/ai/pathing/tile_reached.hpp>
#include <sanguis/server/ai/pathing/update_trail.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/optional_map.hpp>
#include <fcppt/container/maybe_back.hpp>


sanguis::server::ai::pathing::optional_target
sanguis::server::ai::pathing::update_trail(
	sanguis::server::ai::pathing::trail &_trail,
	sanguis::creator::grid const &_grid,
	sanguis::server::entities::with_ai const &_me
)
{
	return
		fcppt::optional_map(
			fcppt::optional_bind(
				fcppt::container::maybe_back(
					_trail
				),
				[
					&_trail,
					&_grid,
					&_me
				](
					sanguis::creator::pos const _next_position
				)
				{
					if(
						sanguis::server::ai::pathing::tile_reached(
							_me,
							_next_position
						)
					)
					{
						_trail.pop_back();

						return
							sanguis::creator::optional_pos(
								fcppt::container::maybe_back(
									_trail
								)
							);
					}

					return
						sanguis::creator::optional_pos(
							_next_position
						);
				}
			),
			[](
				sanguis::creator::pos const _pos
			)
			{
				return
					sanguis::server::ai::pathing::target(
						_pos
					);
			}
		);
}
