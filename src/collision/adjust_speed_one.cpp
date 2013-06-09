#include <sanguis/collision/adjust_speed_one.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/intersection.hpp>
#include <sanguis/collision/optional_vector2.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/rect.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/vector/normalize.hpp>


sanguis::collision::speed const
sanguis::collision::adjust_speed_one(
	sanguis::collision::center const _center,
	sanguis::collision::speed const _speed,
	sanguis::collision::radius const _radius,
	sanguis::collision::rect const _rect,
	sanguis::collision::vector2 const _perp
)
{
	sanguis::collision::vector2 const tangent_pos(
		_center.get()
		+
		fcppt::math::vector::normalize(
			_perp
		)
		*
		_radius.get()
	);

	sanguis::collision::optional_vector2 const intersection(
		sanguis::collision::intersection(
			_rect,
			tangent_pos,
			_speed
		)
	);

	if(
		!intersection
	)
		return
			_speed;

	bool const line_vertical(
		intersection->x() < 0.1f
	);

	bool const line_horizontal(
		intersection->y() < 0.1f
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
