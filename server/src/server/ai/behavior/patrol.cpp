#include <sanguis/duration.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_grid_pos.hpp>
#include <sanguis/server/ai/make_path.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/ai/behavior/patrol.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/random/grid_distance.hpp>
#include <sanguis/server/random/grid_pos_around.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>


sanguis::server::ai::behavior::patrol::patrol(
	sanguis::server::ai::context &_context,
	sanguis::random_generator &_random_generator
)
:
	sanguis::server::ai::behavior::base(),
	context_(
		_context
	),
	random_generator_(
		_random_generator
	),
	start_pos_{
		sanguis::server::world::center_to_grid_pos(
			_context.me().center()
		)
	}
{
}

sanguis::server::ai::behavior::patrol::~patrol()
{
}

bool
sanguis::server::ai::behavior::patrol::do_start()
{
	return
		sanguis::server::ai::make_path(
			context_,
			sanguis::server::random::grid_pos_around(
				random_generator_,
				context_.grid().size(),
				start_pos_,
				sanguis::server::random::grid_distance{
					5u
				}
			)
		);
}

void
sanguis::server::ai::behavior::patrol::do_stop()
{
	context_.clear_path();
}

sanguis::server::ai::behavior::status
sanguis::server::ai::behavior::patrol::update(
	sanguis::duration
)
{
	return
		sanguis::server::ai::go_to_grid_pos(
			context_,
			fcppt::literal<
				sanguis::server::ai::speed_factor
			>(
				0.3f
			)
		);
}
