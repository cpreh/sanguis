#include <sanguis/duration.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/idle.hpp>
#include <sanguis/server/ai/is_patrolling.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/ai/behavior/wander.hpp>
#include <sanguis/server/ai/pathing/optional_target.hpp>
#include <sanguis/server/random/grid_pos.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>


sanguis::server::ai::behavior::wander::wander(
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
	)
{
}

sanguis::server::ai::behavior::wander::~wander()
{
}

bool
sanguis::server::ai::behavior::wander::do_start()
{
	sanguis::creator::grid const &grid(
		context_.grid()
	);

	sanguis::creator::pos const random_pos(
		sanguis::server::random::grid_pos(
			random_generator_,
			grid.size()
		)
	);

	if(
		sanguis::creator::tile_is_solid(
			grid[
				random_pos
			]
		)
	)
		return
			false;

	context_.path_find(
		random_pos
	);

	return
		true;
}

void
sanguis::server::ai::behavior::wander::do_stop()
{
	context_.clear_path();
}

sanguis::server::ai::behavior::status
sanguis::server::ai::behavior::wander::update(
	sanguis::duration
)
{
	sanguis::server::ai::pathing::optional_target const target{
		context_.continue_path()
	};

	if(
		!target
	)
	{
		sanguis::server::ai::idle(
			context_.me()
		);

		return
			sanguis::server::ai::behavior::status::success;
	}

	sanguis::server::ai::rotate_and_move_to_target(
		context_.me(),
		sanguis::server::ai::target{
			sanguis::server::world::grid_pos_to_center(
				target->get()
			)
		},
		sanguis::server::ai::is_patrolling(
			true
		)
	);

	return
		sanguis::server::ai::behavior::status::running;
}
