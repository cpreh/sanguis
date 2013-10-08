#include <sanguis/duration.hpp>
#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/optional_result.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/test_move.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/optional_result.hpp>
#include <sanguis/server/collision/result.hpp>
#include <sanguis/server/collision/with_world_move.hpp>
#include <sanguis/server/entities/with_velocity.hpp>


sanguis::server::collision::optional_result const
sanguis::server::collision::with_world_move(
	sanguis::server::entities::with_velocity const &_with_velocity,
	sanguis::creator::grid const &_grid,
	sanguis::duration const &_duration
)
{
	sanguis::collision::optional_result const result(
		sanguis::collision::test_move(
			sanguis::collision::center(
				_with_velocity.center().get()
			),
			sanguis::collision::dim2(
				_with_velocity.dim()
			),
			sanguis::collision::speed(
				_with_velocity.speed().get()
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
					),
					sanguis::server::center(
						result->center().get()
					)
				)
			)
		:
			sanguis::server::collision::optional_result()
		;
}
