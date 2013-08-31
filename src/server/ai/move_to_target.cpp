#include <sanguis/server/direction.hpp>
#include <sanguis/server/optional_angle.hpp>
#include <sanguis/server/ai/move_to_target.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/current_to_max.hpp>
#include <fcppt/try_dynamic_cast.hpp>


void
sanguis::server::ai::move_to_target(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::optional_angle const _angle
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_velocity *,
		movable,
		&_me
	)
	{
		sanguis::server::entities::property::changeable &speed(
			movable->movement_speed()
		);

		if(
			_angle
		)
		{
			movable->direction(
				sanguis::server::direction(
					_angle->get()
				)
			);

			sanguis::server::entities::property::current_to_max(
				speed
			);
		}
		else
			movable->movement_speed().current(
				0
			);
	}
}
