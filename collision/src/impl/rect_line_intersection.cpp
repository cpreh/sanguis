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
#include <fcppt/config/external_begin.hpp>
#include <boost/units/systems/si/length.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sanguis::collision::impl::optional_intersection const
sanguis::collision::impl::rect_line_intersection(
	sanguis::collision::impl::rect const _rect,
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

	typedef
	std::array<
		sanguis::collision::impl::line_segment,
		4
	>
	line_segment_array;

	line_segment_array const lines{{
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				_rect.pos()
			),
			sanguis::collision::impl::dir(
				sanguis::collision::length2(
					_rect.w(),
					null
				)
			)
		),
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				sanguis::collision::length2(
					_rect.pos().x()
					,
					_rect.pos().y()
					+
					_rect.size().h()
				)
			),
			sanguis::collision::impl::dir(
				sanguis::collision::length2(
					_rect.w(),
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
					_rect.h()
				)
			)
		),
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				sanguis::collision::length2(
					_rect.pos().x()
					+
					_rect.size().w()
					,
					_rect.pos().y()
				)
			),
			sanguis::collision::impl::dir(
				sanguis::collision::length2(
					null,
					_rect.h()
				)
			)
		)
	}};

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
