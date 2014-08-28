#include <sanguis/duration.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_close_to_target.hpp>
#include <sanguis/server/ai/is_patrolling.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/follow_owner.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_links.hpp>


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
		spawn_owner_.get().has_value();
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

	sanguis::server::ai::go_close_to_target(
		context_,
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
