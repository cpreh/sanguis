#include <sanguis/server/direction.hpp>
#include <sanguis/server/optional_angle.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/move_to_target.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/update_interval.hpp>
#include <sanguis/server/collision/distance_entity_pos.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/cast/try_dynamic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::ai::move_to_target(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::optional_angle const _angle,
	sanguis::server::ai::target const _target,
	sanguis::server::ai::speed_factor const _speed_factor
)
{
	fcppt::maybe_void(
		// TODO: Even sentries have a velocity, we could get rid of this dynamic cast
		fcppt::cast::try_dynamic<
			sanguis::server::entities::with_velocity &
		>(
			_me
		),
		[
			_angle,
			_target,
			_speed_factor
		](
			sanguis::server::entities::with_velocity &_movable
		)
		{
			sanguis::server::entities::property::changeable &speed(
				_movable.movement_speed()
			);

			if(
				_angle
			)
			{
				_movable.direction(
					sanguis::server::direction(
						_angle->get()
					)
				);

				// Set the movement at most to 1.3 the speed it would
				// take an entity to reach its target in a single AI
				// tick.
				// TODO: The factor should be dependant upon how fast
				// the target is moving.
				speed.current(
					std::min(
						fcppt::literal<
							sanguis::server::space_unit
						>(
							1.3f
						)
						*
						sanguis::server::collision::distance_entity_pos(
							_movable,
							_target.get().get()
						)
						/
						sanguis::server::ai::update_interval().count()
						,
						speed.max()
						*
						_speed_factor.get()
					)
				);
			}
			else
				speed.current(
					0
				);
		}
	);
}
