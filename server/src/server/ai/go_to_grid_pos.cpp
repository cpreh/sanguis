#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_grid_pos.hpp>
#include <sanguis/server/ai/idle.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <fcppt/optional/maybe.hpp>


sanguis::server::ai::status
sanguis::server::ai::go_to_grid_pos(
	sanguis::server::ai::context &_context,
	sanguis::server::ai::speed_factor const _speed_factor
)
{
	return
		fcppt::optional::maybe(
			_context.continue_path(),
			[
				&_context
			]{
				sanguis::server::ai::idle(
					_context.me()
				);

				return
					sanguis::server::ai::status::success;
			},
			[
				&_context,
				_speed_factor
			](
				sanguis::server::ai::pathing::target const &_target
			)
			{
				sanguis::server::ai::rotate_and_move_to_target(
					_context.me(),
					sanguis::server::ai::target{
						sanguis::server::world::grid_pos_to_center(
							_target.get()
						)
					},
					_speed_factor
				);

				return
					sanguis::server::ai::status::running;
			}
		);

}
