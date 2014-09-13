#include <sanguis/server/angle.hpp>
#include <sanguis/server/ai/rotate_to.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/cast/try_dynamic.hpp>


void
sanguis::server::ai::rotate_to(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::angle const _angle
)
{
	fcppt::maybe_void(
		fcppt::cast::try_dynamic<
			sanguis::server::entities::with_body &
		>(
			_me
		),
		[
			_angle
		](
			sanguis::server::entities::with_body &_with_body
		)
		{
			_with_body.angle(
				_angle
			);
		}
	);
}
