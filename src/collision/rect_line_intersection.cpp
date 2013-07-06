#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/intersection.hpp>
#include <sanguis/collision/line_line_intersect.hpp>
#include <sanguis/collision/line_segment.hpp>
#include <sanguis/collision/optional_intersection.hpp>
#include <sanguis/collision/pos.hpp>
#include <sanguis/collision/rect_line_intersection.hpp>
#include <sanguis/collision/rect.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sanguis::collision::optional_intersection const
sanguis::collision::rect_line_intersection(
	sanguis::collision::rect const _rect,
	sanguis::collision::line_segment const _line
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
		sanguis::collision::line_segment,
		4
	> line_segment_array;

	line_segment_array const lines{{
		sanguis::collision::line_segment(
			sanguis::collision::pos(
				_rect.pos()
			),
			sanguis::collision::dir(
				sanguis::collision::vector2(
					_rect.w(),
					null
				)
			)
		),
		sanguis::collision::line_segment(
			sanguis::collision::pos(
				sanguis::collision::vector2(
					_rect.pos().x(),
					_rect.pos().y() + _rect.size().h()
				)
			),
			sanguis::collision::dir(
				sanguis::collision::vector2(
					_rect.w(),
					null
				)
			)
		),
		sanguis::collision::line_segment(
			sanguis::collision::pos(
				_rect.pos()
			),
			sanguis::collision::dir(
				sanguis::collision::vector2(
					null,
					_rect.h()
				)
			)
		),
		sanguis::collision::line_segment(
			sanguis::collision::pos(
				sanguis::collision::vector2(
					_rect.pos().x() + _rect.size().w(),
					_rect.pos().y()
				)
			),
			sanguis::collision::dir(
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
			sanguis::collision::line_line_intersect(
				_line,
				cur_line
			)
		)
			return
				sanguis::collision::optional_intersection(
					sanguis::collision::intersection(
						cur_line.dir()
					)
				);
	}

	return
		sanguis::collision::optional_intersection();
}
