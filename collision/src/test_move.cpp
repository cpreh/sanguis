#include <sanguis/collision/center.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/collision/impl/is_null.hpp>
#include <sanguis/collision/impl/make_spiral_range.hpp>
#include <sanguis/collision/impl/move.hpp>
#include <sanguis/collision/impl/optional_speed.hpp>
#include <sanguis/collision/impl/test_tile.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/grid_spiral_range.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <fcppt/const.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/cast/to_unsigned_fun.hpp>
#include <fcppt/container/grid/at_optional.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional/alternative.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/map.hpp>


sanguis::collision::optional_result
sanguis::collision::test_move(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius,
	sanguis::collision::speed const _start_speed,
	sanguis::collision::duration const _time,
	sanguis::creator::grid const &_grid
)
{
	if(
		sanguis::collision::impl::is_null(
			_start_speed.x().value()
		)
		&&
		sanguis::collision::impl::is_null(
			_start_speed.y().value()
		)
	)
		return
			sanguis::collision::optional_result();

	sanguis::collision::impl::optional_speed const result(
		fcppt::algorithm::fold(
			sanguis::collision::impl::make_spiral_range(
				sanguis::collision::impl::move(
					_center,
					_start_speed,
					_time
				),
				_radius
			),
			sanguis::collision::impl::optional_speed{},
			[
				_center,
				_radius,
				_time,
				_start_speed,
				&_grid
			](
				sanguis::creator::signed_pos const _entry,
				sanguis::collision::impl::optional_speed const _cur_speed
			)
			{
				sanguis::creator::pos const cur_pos(
					fcppt::math::vector::structure_cast<
						sanguis::creator::pos,
						fcppt::cast::to_unsigned_fun
					>(
						_entry
					)
				);

				sanguis::collision::speed const speed(
					fcppt::optional::from(
						_cur_speed,
						fcppt::const_(
							_start_speed
						)
					)
				);

				return
					fcppt::optional::alternative(
						fcppt::optional::bind(
							fcppt::optional::copy_value(
								fcppt::container::grid::at_optional(
									_grid,
									cur_pos
								)
							),
							[
								_center,
								_radius,
								_time,
								speed,
								cur_pos
							](
								sanguis::creator::tile const _tile
							)
							{
								return
									sanguis::collision::impl::test_tile(
										_center,
										_radius,
										_time,
										speed,
										cur_pos,
										_tile
									);
							}
						),
						sanguis::collision::impl::optional_speed{
							_cur_speed
						}
					);
			}
		)
	);

	return
		fcppt::optional::map(
			result,
			[](
				sanguis::collision::speed const _result_speed
			)
			{
				return
					sanguis::collision::result(
						_result_speed
					);
			}
		);
}
