#include <sanguis/collision/length.hpp>
#include <sanguis/collision/length2.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/intersection.hpp>
#include <sanguis/collision/impl/line_line_intersect.hpp>
#include <sanguis/collision/impl/line_segment.hpp>
#include <sanguis/collision/impl/optional_intersection.hpp>
#include <sanguis/collision/impl/pos.hpp>
#include <sanguis/collision/impl/rect.hpp>
#include <sanguis/collision/impl/rect_line_intersection.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/length.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::collision::impl::optional_intersection
sanguis::collision::impl::rect_line_intersection(
	sanguis::collision::impl::rect const &_rect,
	sanguis::collision::impl::line_segment const _line
)
{
	sanguis::collision::length const null(
		fcppt::literal<
			sanguis::collision::unit
		>(
			0
		)
		*
		boost::units::si::meter
	);

	using
	line_segment_array
	=
	fcppt::array::object<
		sanguis::collision::impl::line_segment,
		4
	>;

	sanguis::collision::impl::rect::dim const size(
		_rect.size()
	);

	line_segment_array const lines{
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				_rect.pos()
			),
			sanguis::collision::impl::dir(
				sanguis::collision::length2(
					size.w(),
					null
				)
			)
		),
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				sanguis::collision::length2(
					_rect.left()
					,
					_rect.bottom()
				)
			),
			sanguis::collision::impl::dir(
				sanguis::collision::length2(
					size.w(),
					null
				)
			)
		),
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				_rect.pos()
			),
			sanguis::collision::impl::dir(
				sanguis::collision::length2(
					null,
					size.h()
				)
			)
		),
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				sanguis::collision::length2(
					_rect.right()
					,
					_rect.top()
				)
			),
			sanguis::collision::impl::dir(
				sanguis::collision::length2(
					null,
					size.h()
				)
			)
		)
	};

	return
		fcppt::algorithm::find_by_opt(
			lines,
			[
				&_line
			](
				sanguis::collision::impl::line_segment const &_cur_line
			)
			{
				return
					sanguis::collision::impl::line_line_intersect(
						_line,
						_cur_line
					)
					?
						sanguis::collision::impl::optional_intersection(
							sanguis::collision::impl::intersection(
								_cur_line.dir()
							)
						)
					:
						sanguis::collision::impl::optional_intersection()
					;
			}
		);
}
