#include <sanguis/server/angle.hpp>
#include <sanguis/server/ai/angle_to_target.hpp>
#include <sanguis/server/ai/rotate_to.hpp>
#include <sanguis/server/ai/rotate_to_target.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sanguis::server::ai::rotate_to_target(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::ai::target const &_target
)
{
	fcppt::optional::maybe_void(
		sanguis::server::ai::angle_to_target(
			_me,
			_target
		),
		[
			&_me
		](
			sanguis::server::angle const _angle_to
		)
		{
			sanguis::server::ai::rotate_to(
				_me,
				_angle_to
			);
		}
	);
}
