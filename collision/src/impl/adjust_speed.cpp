#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/impl/adjust_speed.hpp>
#include <sanguis/collision/impl/intersection.hpp>
#include <sanguis/collision/impl/is_null.hpp>
#include <sanguis/collision/impl/line_segment.hpp>
#include <sanguis/collision/impl/rect.hpp>
#include <sanguis/collision/impl/rect_line_intersection.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/box/expand.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>


sanguis::collision::speed const
sanguis::collision::impl::adjust_speed(
	sanguis::collision::impl::line_segment const _movement,
	sanguis::collision::radius const _radius,
	sanguis::collision::impl::rect const _obstacle,
	sanguis::collision::speed const _old_speed
)
{
	return
		fcppt::maybe(
			sanguis::collision::impl::rect_line_intersection(
				fcppt::math::box::expand(
					_obstacle,
					fcppt::math::vector::fill<
						sanguis::collision::impl::rect::vector
					>(
						_radius.get()
					)
				),
				_movement
			),
			fcppt::const_(
				_old_speed
			),
			[
				_old_speed
			](
				sanguis::collision::impl::intersection const _intersection
			)
			{
				bool const vertical(
					sanguis::collision::impl::is_null(
						_intersection.dir().get().x()
					)
				);

				bool const horizontal(
					sanguis::collision::impl::is_null(
						_intersection.dir().get().y()
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
		);
}
