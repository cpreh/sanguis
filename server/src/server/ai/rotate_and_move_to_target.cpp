#include <sanguis/server/angle.hpp>
#include <sanguis/server/optional_angle.hpp>
#include <sanguis/server/ai/angle_to_target.hpp>
#include <sanguis/server/ai/move_to_target.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/rotate_to.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <fcppt/maybe.hpp>


void
sanguis::server::ai::rotate_and_move_to_target(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::ai::target const _target,
	sanguis::server::ai::speed_factor const _speed_factor
)
{
	fcppt::maybe(
		sanguis::server::ai::angle_to_target(
			_me,
			_target
		),
		[
			&_me,
			_target,
			_speed_factor
		]{
			sanguis::server::ai::move_to_target(
				_me,
				sanguis::server::optional_angle(),
				_target,
				_speed_factor
			);
		},
		[
			&_me
		](
			sanguis::server::angle const _angle_to_target
		)
		{
			sanguis::server::ai::rotate_to(
				_me,
				_angle_to_target
			);
		}
	);
}
