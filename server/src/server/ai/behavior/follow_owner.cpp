#include <sanguis/duration.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_target.hpp>
#include <sanguis/server/ai/in_range.hpp>
#include <sanguis/server/ai/is_patrolling.hpp>
#include <sanguis/server/ai/is_visible.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/follow_owner.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/ai/pathing/is_visible.hpp>
#include <sanguis/server/collision/distance_entity_entity.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/literal.hpp>


sanguis::server::ai::behavior::follow_owner::follow_owner(
	sanguis::server::ai::context &_context,
	sanguis::server::entities::spawn_owner const &_spawn_owner
)
:
	sanguis::server::ai::behavior::base(),
	context_(
		_context
	),
	spawn_owner_{
		_spawn_owner
	}
{
}

sanguis::server::ai::behavior::follow_owner::~follow_owner()
{
}

bool
sanguis::server::ai::behavior::follow_owner::do_start()
{
	return
		spawn_owner_.get()
		&&
		context_.path_find(
			sanguis::server::world::center_to_grid_pos(
				spawn_owner_.get()->center()
			)
		);
}

void
sanguis::server::ai::behavior::follow_owner::do_stop()
{
	context_.clear_path();
}

sanguis::server::ai::behavior::status
sanguis::server::ai::behavior::follow_owner::update(
	sanguis::duration
)
{
	if(
		!spawn_owner_.get()
	)
		return
			sanguis::server::ai::behavior::status::failure;

	sanguis::server::ai::go_to_target(
		context_,
		sanguis::server::ai::in_range{
			sanguis::server::collision::distance_entity_entity(
				context_.me(),
				*spawn_owner_.get()
			)
			<
			// TODO: What should we use here
			fcppt::literal<
				sanguis::server::space_unit
			>(
				100
			)
		},
		sanguis::server::ai::is_visible{
			sanguis::server::ai::pathing::is_visible(
				context_.grid(),
				sanguis::server::world::center_to_grid_pos(
					context_.me().center()
				),
				sanguis::server::world::center_to_grid_pos(
					spawn_owner_.get()->center()
				)
			)
		},
		sanguis::server::ai::target{
			spawn_owner_.get()->center()
		},
		sanguis::server::ai::is_patrolling{
			false
		}
	);

	return
		sanguis::server::ai::behavior::status::running;
}
