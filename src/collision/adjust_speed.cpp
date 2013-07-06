#include <sanguis/collision/adjust_speed.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/is_null.hpp>
#include <sanguis/collision/line_segment.hpp>
#include <sanguis/collision/optional_intersection.hpp>
#include <sanguis/collision/rect.hpp>
#include <sanguis/collision/rect_line_intersection.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/box/expand.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sanguis::collision::speed const
sanguis::collision::adjust_speed(
	sanguis::collision::line_segment const _movement,
	sanguis::collision::dim2 const _entity_size,
	sanguis::collision::rect const _obstacle,
	sanguis::collision::speed const _old_speed
)
{
	sanguis::collision::optional_intersection const intersection(
		sanguis::collision::rect_line_intersection(
			fcppt::math::box::expand(
				_obstacle,
				fcppt::math::dim::structure_cast<
					sanguis::collision::rect::vector
				>(
					_entity_size
					/
					fcppt::literal<
						sanguis::collision::unit
					>(
						2
					)
				)
			),
			_movement
		)
	);

	if(
		!intersection
	)
		return
			_old_speed;

	bool const vertical(
		sanguis::collision::is_null(
			intersection->dir().get().x()
		)
	);

	bool const horizontal(
		sanguis::collision::is_null(
			intersection->dir().get().y()
		)
	);

	FCPPT_ASSERT_ERROR(
		vertical
		!=
		horizontal
	);

	sanguis::collision::unit const zero(
		fcppt::literal<
			sanguis::collision::unit
		>(
			0
		)
	);

	return
		vertical
		?
			sanguis::collision::speed(
				sanguis::collision::vector2(
					zero,
					_old_speed.get().y()
				)
			)
		:
			sanguis::collision::speed(
				sanguis::collision::vector2(
					_old_speed.get().x(),
					zero
				)
			)
		;
}
