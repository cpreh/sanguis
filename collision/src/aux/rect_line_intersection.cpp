#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/aux/dir.hpp>
#include <sanguis/collision/aux/intersection.hpp>
#include <sanguis/collision/aux/line_line_intersect.hpp>
#include <sanguis/collision/aux/line_segment.hpp>
#include <sanguis/collision/aux/optional_intersection.hpp>
#include <sanguis/collision/aux/pos.hpp>
#include <sanguis/collision/aux/rect_line_intersection.hpp>
#include <sanguis/collision/aux/rect.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sanguis::collision::aux::optional_intersection const
sanguis::collision::aux::rect_line_intersection(
	sanguis::collision::aux::rect const _rect,
	sanguis::collision::aux::line_segment const _line
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
		sanguis::collision::aux::line_segment,
		4
	> line_segment_array;

	line_segment_array const lines{{
		sanguis::collision::aux::line_segment(
			sanguis::collision::aux::pos(
				_rect.pos()
			),
			sanguis::collision::aux::dir(
				sanguis::collision::vector2(
					_rect.w(),
					null
				)
			)
		),
		sanguis::collision::aux::line_segment(
			sanguis::collision::aux::pos(
				sanguis::collision::vector2(
					_rect.pos().x(),
					_rect.pos().y() + _rect.size().h()
				)
			),
			sanguis::collision::aux::dir(
				sanguis::collision::vector2(
					_rect.w(),
					null
				)
			)
		),
		sanguis::collision::aux::line_segment(
			sanguis::collision::aux::pos(
				_rect.pos()
			),
			sanguis::collision::aux::dir(
				sanguis::collision::vector2(
					null,
					_rect.h()
				)
			)
		),
		sanguis::collision::aux::line_segment(
			sanguis::collision::aux::pos(
				sanguis::collision::vector2(
					_rect.pos().x() + _rect.size().w(),
					_rect.pos().y()
				)
			),
			sanguis::collision::aux::dir(
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
			sanguis::collision::aux::line_line_intersect(
				_line,
				cur_line
			)
		)
			return
				sanguis::collision::aux::optional_intersection(
					sanguis::collision::aux::intersection(
						cur_line.dir()
					)
				);
	}

	return
		sanguis::collision::aux::optional_intersection();
}
