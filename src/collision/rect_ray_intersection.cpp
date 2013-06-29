#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/intersection.hpp>
#include <sanguis/collision/line_segment.hpp>
#include <sanguis/collision/optional_intersection.hpp>
#include <sanguis/collision/optional_unit.hpp>
#include <sanguis/collision/pos.hpp>
#include <sanguis/collision/ray_line_intersection.hpp>
#include <sanguis/collision/rect_ray_intersection.hpp>
#include <sanguis/collision/rect.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length_square.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sanguis::collision::optional_intersection const
sanguis::collision::rect_ray_intersection(
	sanguis::collision::rect const _rect,
	sanguis::collision::pos const _pos,
	sanguis::collision::dir const _dir
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

	sanguis::collision::optional_unit nearest_distance;

	typedef
	fcppt::optional<
		sanguis::collision::dir
	> optional_dir;

	optional_dir result_dir;

	for(
		auto const &line : lines
	)
	{
		sanguis::collision::optional_unit const contact_distance(
			sanguis::collision::ray_line_intersection(
				_pos,
				_dir,
				line
			)
		);

		if(
			!contact_distance
		)
			continue;

		if(
			!nearest_distance
			||
			*contact_distance
			<
			*nearest_distance
		)
		{
			nearest_distance
				= *contact_distance;

			result_dir =
				optional_dir(
					line.dir()
				);
		}
	}

	return
		result_dir
		?
			sanguis::collision::optional_intersection(
				sanguis::collision::intersection(
					*result_dir,
					*nearest_distance
				)
			)
		:
			sanguis::collision::optional_intersection()
		;
}
