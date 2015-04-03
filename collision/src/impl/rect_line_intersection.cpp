#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/intersection.hpp>
#include <sanguis/collision/impl/line_line_intersect.hpp>
#include <sanguis/collision/impl/line_segment.hpp>
#include <sanguis/collision/impl/optional_intersection.hpp>
#include <sanguis/collision/impl/pos.hpp>
#include <sanguis/collision/impl/rect.hpp>
#include <sanguis/collision/impl/rect_line_intersection.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sanguis::collision::impl::optional_intersection const
sanguis::collision::impl::rect_line_intersection(
	sanguis::collision::impl::rect const _rect,
	sanguis::collision::impl::line_segment const _line
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
		sanguis::collision::impl::line_segment,
		4
	> line_segment_array;

	line_segment_array const lines{{
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				_rect.pos()
			),
			sanguis::collision::impl::dir(
				sanguis::collision::vector2(
					_rect.w(),
					null
				)
			)
		),
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				sanguis::collision::vector2(
					_rect.pos().x(),
					_rect.pos().y() + _rect.size().h()
				)
			),
			sanguis::collision::impl::dir(
				sanguis::collision::vector2(
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
				sanguis::collision::vector2(
					null,
					_rect.h()
				)
			)
		),
		sanguis::collision::impl::line_segment(
			sanguis::collision::impl::pos(
				sanguis::collision::vector2(
					_rect.pos().x() + _rect.size().w(),
					_rect.pos().y()
				)
			),
			sanguis::collision::impl::dir(
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
			sanguis::collision::impl::line_line_intersect(
				_line,
				cur_line
			)
		)
			return
				sanguis::collision::impl::optional_intersection(
					sanguis::collision::impl::intersection(
						cur_line.dir()
					)
				);
	}

	return
		sanguis::collision::impl::optional_intersection();
}
