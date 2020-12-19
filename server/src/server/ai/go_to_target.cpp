#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_target.hpp>
#include <sanguis/server/ai/in_range.hpp>
#include <sanguis/server/ai/is_visible.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/rotate_to_target.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/stop.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/pathing/positions_are_close.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <fcppt/const.hpp>
#include <fcppt/optional/maybe.hpp>


bool
sanguis::server::ai::go_to_target(
	sanguis::server::ai::context &_context,
	sanguis::server::ai::in_range const _in_range,
	sanguis::server::ai::is_visible const _is_visible,
	sanguis::server::ai::target const &_target,
	sanguis::server::ai::speed_factor const _speed_factor
)
{
	if(
		_is_visible.get()
	)
	{
		if(
			_in_range.get()
		)
		{
			sanguis::server::ai::stop(
				_context.me()
			);

			sanguis::server::ai::rotate_to_target(
				_context.me(),
				_target
			);

			_context.clear_path();
		}
		else
		{
			sanguis::server::ai::rotate_and_move_to_target(
				_context.me(),
				_target,
				_speed_factor
			);
		}

		return
			true;
	}

	sanguis::creator::pos const target_grid_pos{
		sanguis::server::world::center_to_grid_pos(
			_target.get()
		)
	};

	return
		fcppt::optional::maybe(
			_context.destination(),
			fcppt::const_(
				false
			),
			[
				target_grid_pos
			](
				sanguis::creator::pos const &_destination
			)
			{
				return
					!sanguis::server::ai::pathing::positions_are_close(
						_destination,
						target_grid_pos
					);
			}
		)
		?
			_context.path_find(
				target_grid_pos
			)
		:
			fcppt::optional::maybe(
				_context.continue_path(),
				[
					&_context,
					target_grid_pos
				]{
					return
						_context.path_find(
							target_grid_pos
						);
				},
				[
					&_context,
					_speed_factor
				](
					sanguis::server::ai::pathing::target const &_grid_target
				)
				{
					sanguis::server::ai::rotate_and_move_to_target(
						_context.me(),
						sanguis::server::ai::target{
							sanguis::server::world::grid_pos_to_center(
								_grid_target.get()
							)
						},
						_speed_factor
					);

					return
						true;
				}
			)
		;
}
