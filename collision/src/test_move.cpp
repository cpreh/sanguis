#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/aux_/adjust_speed.hpp>
#include <sanguis/collision/aux_/dir.hpp>
#include <sanguis/collision/aux_/is_null.hpp>
#include <sanguis/collision/aux_/line_segment.hpp>
#include <sanguis/collision/aux_/make_spiral_range.hpp>
#include <sanguis/collision/aux_/pos.hpp>
#include <sanguis/collision/aux_/rect.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/grid_spiral_range.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_rect.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/math/box/intersects.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::collision::optional_result const
sanguis::collision::test_move(
	sanguis::collision::center const _center,
	sanguis::collision::dim2 const _size,
	sanguis::collision::speed const _speed,
	sanguis::collision::duration const _time,
	sanguis::creator::grid const &_grid
)
{
	if(
		sanguis::collision::aux_::is_null(
			_speed.get().x()
		)
		&&
		sanguis::collision::aux_::is_null(
			_speed.get().y()
		)
	)
		return
			sanguis::collision::optional_result();

	sanguis::collision::speed new_speed(
		_speed
	);

	bool changed(
		false
	);

	for(
		auto const &entry
		:
		sanguis::collision::aux_::make_spiral_range(
			sanguis::collision::center(
				_center.get()
				+
				_speed.get()
				*
				_time.count()
			),
			_size
		)
	)
	{
		sanguis::creator::pos const cur_pos(
			fcppt::math::vector::structure_cast<
				sanguis::creator::pos
			>(
				entry
			)
		);

		if(
			!fcppt::container::grid::in_range(
				_grid,
				cur_pos
			)
		)
			continue;

		sanguis::creator::tile const cur_tile(
			_grid[
				cur_pos
			]
		);

		if(
			!sanguis::creator::tile_is_solid(
				cur_tile
			)
		)
			continue;

		sanguis::collision::center const new_center(
			_center.get()
			+
			new_speed.get()
			*
			_time.count()
		);

		sanguis::collision::aux_::rect const rect(
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

		sanguis::creator::rect const tile_rect(
			sanguis::creator::tile_rect(
				cur_tile
			)
		);

		sanguis::collision::aux_::rect const entry_rect(
			fcppt::math::vector::structure_cast<
				sanguis::collision::aux_::rect::vector
			>(
				tile_rect.pos()
			)
			+
			fcppt::math::vector::structure_cast<
				sanguis::collision::aux_::rect::vector
			>(
				cur_pos
				*
				sanguis::creator::tile_size::value
			),
			fcppt::math::dim::structure_cast<
				sanguis::collision::aux_::rect::dim
			>(
				tile_rect.size()
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
			sanguis::collision::aux_::adjust_speed(
				sanguis::collision::aux_::line_segment(
					sanguis::collision::aux_::pos(
						_center.get()
					),
					sanguis::collision::aux_::dir(
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
