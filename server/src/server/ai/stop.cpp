#include <sanguis/server/ai/stop.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/cast/try_dynamic.hpp>


void
sanguis::server::ai::stop(
	sanguis::server::entities::with_ai &_me
)
{
	fcppt::maybe_void(
		fcppt::cast::try_dynamic<
			sanguis::server::entities::with_velocity &
		>(
			_me
		),
		[](
			sanguis::server::entities::with_velocity &_movable
		)
		{
			_movable.movement_speed().current(
				0
			);
		}
	);
}
