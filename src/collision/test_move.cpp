#include <sanguis/duration.hpp>
#include <sanguis/collision/adjust_speed.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/is_null.hpp>
#include <sanguis/collision/line_segment.hpp>
#include <sanguis/collision/make_range.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/pos.hpp>
#include <sanguis/collision/rect.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/grid_crange.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/box/intersects.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::collision::optional_result const
sanguis::collision::test_move(
	sanguis::collision::center const _center,
	sanguis::collision::dim2 const _size,
	sanguis::collision::speed const _speed,
	sanguis::duration const _time,
	sanguis::creator::grid const &_grid
)
{
	if(
		sanguis::collision::is_null(
			_speed.get().x()
		)
		&&
		sanguis::collision::is_null(
			_speed.get().y()
		)
	)
		return
			sanguis::collision::optional_result();

	sanguis::collision::center const new_center(
		_center.get()
		+
		_speed.get()
		*
		_time.count()
	);

	sanguis::collision::rect const rect(
		new_center.get()
		-
		_size
		/
		fcppt::literal<
			sanguis::collision::unit
		>(
			2
		)
		,
		_size
	);

	sanguis::collision::speed new_speed(
		_speed
	);

	bool changed(
		false
	);

	for(
		auto const &entry
		:
		sanguis::collision::make_range(
			_grid,
			new_center,
			_size
		)
	)
	{
		if(
			!sanguis::creator::tile_is_solid(
				entry.value()
			)
		)
			continue;

		sanguis::collision::rect const entry_rect(
			fcppt::math::vector::structure_cast<
				sanguis::collision::rect::vector
			>(
				entry.pos()
				*
				sanguis::creator::tile_size::value
			),
			fcppt::math::dim::fill<
				sanguis::collision::rect::dim::dim_wrapper::value
			>(
				static_cast<
					sanguis::collision::unit
				>(
					sanguis::creator::tile_size::value
				)
			)
		);

		if(
			!fcppt::math::box::intersects(
				rect,
				entry_rect
			)
		)
			continue;

		new_speed =
			sanguis::collision::adjust_speed(
				sanguis::collision::line_segment(
					sanguis::collision::pos(
						_center.get()
					),
					sanguis::collision::dir(
						new_center.get()
						-
						_center.get()
					)
				),
				rect.size(),
				entry_rect,
				new_speed
			);

		changed = true;
	}

	return
		changed
		?
			sanguis::collision::optional_result(
				sanguis::collision::result(
					new_speed,
					_center
				)
			)
		:
			sanguis::collision::optional_result()
		;
}
