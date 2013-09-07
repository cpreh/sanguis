#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/aux/adjust_speed.hpp>
#include <sanguis/collision/aux/is_null.hpp>
#include <sanguis/collision/aux/line_segment.hpp>
#include <sanguis/collision/aux/optional_intersection.hpp>
#include <sanguis/collision/aux/rect.hpp>
#include <sanguis/collision/aux/rect_line_intersection.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/box/expand.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sanguis::collision::speed const
sanguis::collision::aux::adjust_speed(
	sanguis::collision::aux::line_segment const _movement,
	sanguis::collision::dim2 const _entity_size,
	sanguis::collision::aux::rect const _obstacle,
	sanguis::collision::speed const _old_speed
)
{
	sanguis::collision::aux::optional_intersection const intersection(
		sanguis::collision::aux::rect_line_intersection(
			fcppt::math::box::expand(
				_obstacle,
				fcppt::math::dim::structure_cast<
					sanguis::collision::aux::rect::vector
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
		sanguis::collision::aux::is_null(
			intersection->dir().get().x()
		)
	);

	bool const horizontal(
		sanguis::collision::aux::is_null(
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
