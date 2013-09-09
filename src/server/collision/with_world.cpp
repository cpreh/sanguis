#include <sanguis/duration.hpp>
#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/optional_result.hpp>
#include <sanguis/server/collision/result.hpp>
#include <sanguis/server/collision/with_world.hpp>
#include <sanguis/server/entities/speed.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sanguis::server::collision::optional_result const
sanguis::server::collision::with_world(
	sanguis::server::entities::with_body const &_with_body,
	sanguis::creator::grid const &_grid,
	sanguis::duration const &_duration
)
{
	sanguis::server::space_unit const pixels_per_meter(
		fcppt::cast::int_to_float<
			sanguis::server::space_unit
		>(
			sanguis::pixels_per_meter()
		)
	);

	sanguis::collision::optional_result const result(
		sanguis::collision::test_move(
			sanguis::collision::center(
				_with_body.center().get()
				*
				pixels_per_meter
			),
			fcppt::math::dim::fill<
				sanguis::collision::dim2::dim_wrapper::value
			>(
				_with_body.radius().get()
				*
				fcppt::ltieral<
					sanguis::collision::unit
				>(
					2
				)
				*
				pixels_per_meter
			),
			sanguis::collision::speed(
				sanguis::server::entities::speed(
					_with_body
				).get()
				*
				pixels_per_meter
			),
			_duration,
			_grid
		)
	);

	return
		result
		?
			sanguis::server::collision::optional_result(
				sanguis::server::collision::result(
					sanguis::server::speed(
						result->speed().get()
						/
						pixels_per_meter
					),
					sanguis::server::center(
						result->center().get()
						/
						pixels_per_meter
					)
				)
			)
		:
			sanguis::server::collision::optional_result()
		;
}
