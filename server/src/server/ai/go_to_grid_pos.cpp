#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_grid_pos.hpp>
#include <sanguis/server/ai/idle.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/ai/pathing/optional_target.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>


sanguis::server::ai::behavior::status
sanguis::server::ai::go_to_grid_pos(
	sanguis::server::ai::context &_context,
	sanguis::server::ai::speed_factor const _speed_factor
)
{
	sanguis::server::ai::pathing::optional_target const target{
		_context.continue_path()
	};

	if(
		!target
	)
	{
		sanguis::server::ai::idle(
			_context.me()
		);

		return
			sanguis::server::ai::behavior::status::success;
	}

	sanguis::server::ai::rotate_and_move_to_target(
		_context.me(),
		sanguis::server::ai::target{
			sanguis::server::world::grid_pos_to_center(
				target->get()
			)
		},
		_speed_factor
	);

	return
		sanguis::server::ai::behavior::status::running;

}
