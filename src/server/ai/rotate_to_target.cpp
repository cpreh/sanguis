#include <sanguis/server/angle.hpp>
#include <sanguis/server/ai/rotate_to_target.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/try_dynamic_cast.hpp>


void
sanguis::server::ai::rotate_to_target(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::angle const _angle
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_body *,
		with_body,
		&_me
	)
		with_body->angle(
			_angle
		);
}
