#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/collision/impl/adjust_speed.hpp>
#include <sanguis/collision/impl/dir.hpp>
#include <sanguis/collision/impl/duration_to_time.hpp>
#include <sanguis/collision/impl/grid_to_meter.hpp>
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
#include <fcppt/maybe_void.hpp>
#include <fcppt/make_literal_boost_units.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/math/box/expand.hpp>
#include <fcppt/math/box/intersects.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/map.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/map.hpp>
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
			_speed.x().value()
		)
		&&
		sanguis::collision::impl::is_null(
			_speed.y().value()
		)
	)
		return
			sanguis::collision::optional_result();

	sanguis::collision::speed new_speed(
		_speed
	);

	// TODO: Use an algorithm for this
	bool changed(
		false
	);

	auto const elapsed_time(
		sanguis::collision::impl::duration_to_time(
			_time
		)
	);

	for(
		sanguis::creator::signed_pos const entry
		:
		sanguis::collision::impl::make_spiral_range(
			sanguis::collision::center(
				_center.get()
				+
				_speed
				*
				elapsed_time
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

		fcppt::maybe_void(
			fcppt::container::grid::at_optional(
				_grid,
				cur_pos
			),
			[
				_center,
				_radius,
				_time,
				cur_pos,
				elapsed_time,
				&changed,
				&new_speed
			](
				sanguis::creator::tile const _cur_tile
			)
			{
				if(
					!sanguis::creator::tile_is_solid(
						_cur_tile
					)
				)
					return;

				sanguis::collision::center const new_center(
					_center.get()
					+
					new_speed
					*
					elapsed_time
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
						_cur_tile
					)
				);

				sanguis::collision::impl::rect const entry_rect(
					fcppt::math::vector::map(
						tile_rect.pos(),
						&sanguis::collision::impl::grid_to_meter
					)
					+
					fcppt::math::vector::map(
						cur_pos
						*
						sanguis::creator::tile_size::value
						,
						&sanguis::collision::impl::grid_to_meter
					),
					fcppt::math::dim::map(
						tile_rect.size(),
						&sanguis::collision::impl::grid_to_meter
					)
				);

				if(
					!fcppt::math::box::intersects(
						rect,
						entry_rect
					)
				)
					return;

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

				changed =
					true;
			}
		);
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
