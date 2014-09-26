#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/aux_/dir.hpp>
#include <sanguis/collision/aux_/intersection.hpp>
#include <sanguis/collision/aux_/line_line_intersect.hpp>
#include <sanguis/collision/aux_/line_segment.hpp>
#include <sanguis/collision/aux_/optional_intersection.hpp>
#include <sanguis/collision/aux_/pos.hpp>
#include <sanguis/collision/aux_/rect.hpp>
#include <sanguis/collision/aux_/rect_line_intersection.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sanguis::collision::aux_::optional_intersection const
sanguis::collision::aux_::rect_line_intersection(
	sanguis::collision::aux_::rect const _rect,
	sanguis::collision::aux_::line_segment const _line
)
{
	sanguis::collision::unit const null(
		fcppt::literal<
			sanguis::collision::unit
		>(
			0
		)
	);

	typedef std::array<
		sanguis::collision::aux_::line_segment,
		4
	> line_segment_array;

	line_segment_array const lines{{
		sanguis::collision::aux_::line_segment(
			sanguis::collision::aux_::pos(
				_rect.pos()
			),
			sanguis::collision::aux_::dir(
				sanguis::collision::vector2(
					_rect.w(),
					null
				)
			)
		),
		sanguis::collision::aux_::line_segment(
			sanguis::collision::aux_::pos(
				sanguis::collision::vector2(
					_rect.pos().x(),
					_rect.pos().y() + _rect.size().h()
				)
			),
			sanguis::collision::aux_::dir(
				sanguis::collision::vector2(
					_rect.w(),
					null
				)
			)
		),
		sanguis::collision::aux_::line_segment(
			sanguis::collision::aux_::pos(
				_rect.pos()
			),
			sanguis::collision::aux_::dir(
				sanguis::collision::vector2(
					null,
					_rect.h()
				)
			)
		),
		sanguis::collision::aux_::line_segment(
			sanguis::collision::aux_::pos(
				sanguis::collision::vector2(
					_rect.pos().x() + _rect.size().w(),
					_rect.pos().y()
				)
			),
			sanguis::collision::aux_::dir(
				sanguis::collision::vector2(
					null,
					_rect.h()
				)
			)
		)
	}};

	for(
		auto const &cur_line : lines
	)
	{
		if(
			sanguis::collision::aux_::line_line_intersect(
				_line,
				cur_line
			)
		)
			return
				sanguis::collision::aux_::optional_intersection(
					sanguis::collision::aux_::intersection(
						cur_line.dir()
					)
				);
	}

	return
		sanguis::collision::aux_::optional_intersection();
}
