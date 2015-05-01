#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/collision/impl/adjust_speed.hpp>
#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/is_null.hpp>
#include <sanguis/collision/impl/line_segment.hpp>
#include <sanguis/collision/impl/make_spiral_range.hpp>
#include <sanguis/collision/impl/pos.hpp>
#include <sanguis/collision/impl/rect.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/grid_spiral_range.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/rect.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <sanguis/creator/tile_rect.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/container/grid/in_range.hpp>
#include <fcppt/math/box/expand.hpp>
#include <fcppt/math/box/intersects.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::collision::optional_result const
sanguis::collision::test_move(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius,
	sanguis::collision::speed const _speed,
	sanguis::collision::duration const _time,
	sanguis::creator::grid const &_grid
)
{

	if(
		sanguis::collision::impl::is_null(
			_speed.get().x()
		)
		&&
		sanguis::collision::impl::is_null(
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
		sanguis::creator::signed_pos const entry
		:
		sanguis::collision::impl::make_spiral_range(
			sanguis::collision::center(
				_center.get()
				+
				_speed.get()
				*
				_time.count()
			),
			_radius
		)
	)
	{
		sanguis::creator::pos const cur_pos(
			fcppt::math::vector::structure_cast<
				sanguis::creator::pos,
				fcppt::cast::to_unsigned_fun
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

		sanguis::collision::impl::rect const rect(
			fcppt::math::box::expand(
				sanguis::collision::impl::rect(
					new_center.get(),
					sanguis::collision::impl::rect::dim::null()
				),
				fcppt::math::vector::fill<
					sanguis::collision::impl::rect::vector
				>(
					_radius.get()
				)
			)
		);

		sanguis::creator::rect const tile_rect(
			sanguis::creator::tile_rect(
				cur_tile
			)
		);

		sanguis::collision::impl::rect const entry_rect(
			fcppt::math::vector::structure_cast<
				sanguis::collision::impl::rect::vector,
				fcppt::cast::int_to_float_fun
			>(
				tile_rect.pos()
			)
			+
			fcppt::math::vector::structure_cast<
				sanguis::collision::impl::rect::vector,
				fcppt::cast::int_to_float_fun
			>(
				cur_pos
				*
				sanguis::creator::tile_size::value
			),
			fcppt::math::dim::structure_cast<
				sanguis::collision::impl::rect::dim,
				fcppt::cast::int_to_float_fun
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
			sanguis::collision::impl::adjust_speed(
				sanguis::collision::impl::line_segment(
					sanguis::collision::impl::pos(
						_center.get()
					),
					sanguis::collision::impl::dir(
						new_center.get()
						-
						_center.get()
					)
				),
				_radius,
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
					new_speed
				)
			)
		:
			sanguis::collision::optional_result()
		;
}
