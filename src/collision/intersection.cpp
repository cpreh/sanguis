#include <sanguis/collision/intersection.hpp>
#include <sanguis/collision/line_segment.hpp>
#include <sanguis/collision/optional_vector2.hpp>
#include <sanguis/collision/ray_line_intersect.hpp>
#include <sanguis/collision/rect.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sanguis::collision::optional_vector2 const
sanguis::collision::intersection(
	sanguis::collision::rect const _rect,
	sanguis::collision::vector2 const _pos,
	sanguis::collision::speed const _speed
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
			_rect.pos(),
			sanguis::collision::vector2(
				_rect.w(),
				null
			)
		),
		sanguis::collision::line_segment(
			sanguis::collision::vector2(
				_rect.pos().x(),
				_rect.pos().y() + _rect.size().h()
			),
			sanguis::collision::vector2(
				_rect.w(),
				null
			)
		),
		sanguis::collision::line_segment(
			_rect.pos(),
			sanguis::collision::vector2(
				null,
				_rect.h()
			)
		),
		sanguis::collision::line_segment(
			sanguis::collision::vector2(
				_rect.pos().x() + _rect.size().w(),
				_rect.pos().y()
			),
			sanguis::collision::vector2(
				null,
				_rect.h()
			)
		)
	}};

	for(
		auto const &line : lines
	)
		if(
			sanguis::collision::ray_line_intersect(
				_pos,
				_speed,
				line
			)
		)
			return
				sanguis::collision::optional_vector2(
					line.dir()
				);

	return
		sanguis::collision::optional_vector2();
}
