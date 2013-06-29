#include <sanguis/duration.hpp>
#include <sanguis/collision/adjust_speed.hpp>
#include <sanguis/collision/both_intersections.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dir.hpp>
#include <sanguis/collision/intersection_pair.hpp>
#include <sanguis/collision/is_null.hpp>
#include <sanguis/collision/make_range.hpp>
#include <sanguis/collision/make_tangent_pos.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/pos.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/collision/vector2.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/grid_crange.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sanguis::collision::optional_result const
sanguis::collision::test_move(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius,
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

	sanguis::collision::pos const tangent1_pos(
		sanguis::collision::make_tangent_pos(
			_center,
			_radius,
			sanguis::collision::vector2(
				_speed.get().y(),
				-_speed.get().x()
			)
		)
	);

	sanguis::collision::pos const tangent2_pos(
		sanguis::collision::make_tangent_pos(
			_center,
			_radius,
			sanguis::collision::vector2(
				-_speed.get().y(),
				_speed.get().x()
			)
		)
	);

	sanguis::collision::intersection_pair intersection;

	for(
		auto const &entry
		:
		sanguis::collision::make_range(
			_grid,
			new_center,
			_radius
		)
	)
	{
		if(
			!sanguis::creator::tile_is_solid(
				entry.value()
			)
		)
			continue;

		intersection.merge(
			sanguis::collision::both_intersections(
				entry.pos(),
				sanguis::collision::dir(
					_speed.get()
				),
				tangent1_pos,
				tangent2_pos
			)
		);
	}

	sanguis::collision::speed new_speed(
		_speed
	);

	if(
		intersection.first()
	)
		new_speed =
			sanguis::collision::adjust_speed(
				*intersection.first(),
				new_speed
			);

	if(
		intersection.second()
	)
		new_speed =
			sanguis::collision::adjust_speed(
				*intersection.second(),
				new_speed
			);

	return
		intersection.first()
		||
		intersection.second()
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
