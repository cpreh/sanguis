#include <sanguis/collision/world/body_exit.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/server/collision/body_exit.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <fcppt/cast/static_downcast.hpp>


void
sanguis::server::collision::body_exit(
	sanguis::collision::world::body_exit_container const &_body_exit_container
)
{
	for(
		sanguis::collision::world::body_exit const &body_exit
		:
		_body_exit_container
	)
		fcppt::cast::static_downcast<
			sanguis::server::collision::ghost_base &
		>(
			body_exit.ghost()
		).body_exit_callback()(
			body_exit.body()
		);
}
