#include <sanguis/collision/adjust_speed.hpp>
#include <sanguis/collision/intersection.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/error.hpp>


sanguis::collision::speed const
sanguis::collision::adjust_speed(
	sanguis::collision::intersection const _intersection,
	sanguis::collision::speed const _speed
)
{
	bool const line_vertical(
		_intersection.dir().get().x() < 0.1f
	);

	bool const line_horizontal(
		_intersection.dir().get().y() < 0.1f
	);

	FCPPT_ASSERT_ERROR(
		line_vertical != line_horizontal
	);

	return
		line_vertical
		?
			sanguis::collision::speed(
				sanguis::collision::vector2(
					fcppt::literal<
						sanguis::collision::unit
					>(
						0
					),
					_speed.get().y()
				)
			)
		:
			sanguis::collision::speed(
				sanguis::collision::vector2(
					_speed.get().x(),
					fcppt::literal<
						sanguis::collision::unit
					>(
						0
					)
				)
			)
		;
}
