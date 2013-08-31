#include <sanguis/server/ai/stop.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <fcppt/try_dynamic_cast.hpp>


void
sanguis::server::ai::stop(
	sanguis::server::entities::with_ai &_me
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_velocity *,
		movable,
		&_me
	)
		movable->movement_speed().current(
			0
		);
}
