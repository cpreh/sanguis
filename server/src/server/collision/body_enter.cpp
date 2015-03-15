#include <sanguis/collision/world/body_enter.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/collision/body_enter.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <fcppt/cast/static_downcast.hpp>


void
sanguis::server::collision::body_enter(
	sanguis::collision::world::body_enter_container const &_body_enter_container
)
{
	for(
		sanguis::collision::world::body_enter const &body_enter
		:
		_body_enter_container
	)
		fcppt::cast::static_downcast<
			sanguis::server::collision::ghost_base &
		>(
			body_enter.ghost()
		).body_enter(
			body_enter.body(),
			body_enter.created()
		);
}
