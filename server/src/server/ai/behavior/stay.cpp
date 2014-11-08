#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_grid_pos.hpp>
#include <sanguis/server/ai/is_patrolling.hpp>
#include <sanguis/server/ai/make_path.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/ai/behavior/stay.hpp>
#include <sanguis/server/collision/distance_pos_pos.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/literal.hpp>


sanguis::server::ai::behavior::stay::stay(
	sanguis::server::ai::context &_context
)
:
	sanguis::server::ai::behavior::base(),
	context_(
		_context
	),
	start_pos_{
		_context.me().center()
	}
{
}

sanguis::server::ai::behavior::stay::~stay()
{
}

bool
sanguis::server::ai::behavior::stay::do_start()
{
	if(
		sanguis::server::collision::distance_pos_pos(
			start_pos_.get(),
			context_.me().center().get()
		)
		<
		fcppt::literal<
			sanguis::server::space_unit
		>(
			// TODO
			500.f
		)
	)
		return
			false;

	return
		sanguis::server::ai::make_path(
			context_,
			sanguis::server::world::center_to_grid_pos(
				start_pos_
			)
		);
}

void
sanguis::server::ai::behavior::stay::do_stop()
{
	context_.clear_path();
}

sanguis::server::ai::behavior::status
sanguis::server::ai::behavior::stay::update(
	sanguis::duration
)
{
	return
		sanguis::server::ai::go_to_grid_pos(
			context_,
			sanguis::server::ai::is_patrolling{
				false
			}
		);
}
