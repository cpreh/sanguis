#include <sanguis/server/angle.hpp>
#include <sanguis/server/ai/rotate_to.hpp>
#include <sanguis/server/entities/with_ai.hpp>


void
sanguis::server::ai::rotate_to(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::angle const _angle
)
{
	_me.angle(
		_angle
	);
}
