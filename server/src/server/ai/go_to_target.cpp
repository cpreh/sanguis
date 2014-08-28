#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_target.hpp>
#include <sanguis/server/ai/in_range.hpp>
#include <sanguis/server/ai/is_patrolling.hpp>
#include <sanguis/server/ai/is_visible.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/rotate_to_target.hpp>
#include <sanguis/server/ai/stop.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/pathing/optional_target.hpp>
#include <sanguis/server/ai/pathing/positions_are_close.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>


void
sanguis::server::ai::go_to_target(
	sanguis::server::ai::context &_context,
	sanguis::server::ai::in_range const _in_range,
	sanguis::server::ai::is_visible const _is_visible,
	sanguis::server::ai::target const _target,
	sanguis::server::ai::is_patrolling const _is_patrolling
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
			sanguis::server::ai::rotate_and_move_to_target(
				_context.me(),
				_target,
				_is_patrolling
			);

		return;
	}

	sanguis::server::ai::pathing::optional_target const grid_target{
		_context.continue_path()
	};

	if(
		grid_target
	)
	{
		sanguis::server::ai::rotate_and_move_to_target(
			_context.me(),
			sanguis::server::ai::target{
				sanguis::server::world::grid_pos_to_center(
					grid_target->get()
				)
			},
			_is_patrolling
		);

		return;
	}

	sanguis::creator::pos const target_grid_pos{
		sanguis::server::world::center_to_grid_pos(
			_target.get()
		)
	};

	if(
		!grid_target
		||
		!sanguis::server::ai::pathing::positions_are_close(
			grid_target->get(),
			target_grid_pos
		)
	)
		_context.path_find(
			target_grid_pos
		);
}
