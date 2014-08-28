#include <sanguis/server/optional_angle.hpp>
#include <sanguis/server/ai/angle_to_target.hpp>
#include <sanguis/server/ai/rotate_to.hpp>
#include <sanguis/server/ai/rotate_to_target.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/entities/with_ai.hpp>


void
sanguis::server::ai::rotate_to_target(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::ai::target const _target
)
{
	sanguis::server::optional_angle const angle_to(
		sanguis::server::ai::angle_to_target(
			_me,
			_target
		)
	);

	if(
		angle_to
	)
		sanguis::server::ai::rotate_to(
			_me,
			*angle_to
		);
}
