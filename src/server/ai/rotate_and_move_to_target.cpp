#include <sanguis/server/center.hpp>
#include <sanguis/server/optional_angle.hpp>
#include <sanguis/server/ai/angle_to_target.hpp>
#include <sanguis/server/ai/move_to_target.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/rotate_to_target.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>


void
sanguis::server::ai::rotate_and_move_to_target(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::center const _target
)
{
	sanguis::server::optional_angle const angle_to_target(
		sanguis::server::ai::angle_to_target(
			_me,
			_target
		)
	);

	if(
		angle_to_target
	)
		sanguis::server::ai::rotate_to_target(
			_me,
			*angle_to_target
		);

	sanguis::server::ai::move_to_target(
		_me,
		angle_to_target
	);
}
