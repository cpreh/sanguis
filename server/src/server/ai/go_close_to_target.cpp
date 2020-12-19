#include <sanguis/creator/tile_is_visible.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/go_close_to_target.hpp>
#include <sanguis/server/ai/go_to_target.hpp>
#include <sanguis/server/ai/in_range.hpp>
#include <sanguis/server/ai/is_visible.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/collision/distance_entity_pos.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/literal.hpp>


bool
sanguis::server::ai::go_close_to_target(
	sanguis::server::ai::context &_context,
	sanguis::server::ai::target const &_target,
	sanguis::server::ai::speed_factor const _speed_factor
)
{
	return
		sanguis::server::ai::go_to_target(
			_context,
			sanguis::server::ai::in_range{
				sanguis::server::collision::distance_entity_pos(
					_context.me(),
					_target.get().get()
				)
				<
				fcppt::literal<
					sanguis::server::space_unit
				>(
					100
				)
			},
			sanguis::server::ai::is_visible{
				sanguis::creator::tile_is_visible(
					_context.grid(),
					sanguis::server::world::center_to_grid_pos(
						_context.me().center()
					),
					sanguis::server::world::center_to_grid_pos(
						_target.get()
					)
				)
			},
			_target,
			_speed_factor
		);
}
