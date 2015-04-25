#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/test.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/with_world.hpp>


bool
sanguis::server::collision::with_world(
	sanguis::server::center const _center,
	sanguis::server::radius const _radius,
	sanguis::creator::grid const &_grid
)
{
	return
		sanguis::collision::test(
			sanguis::collision::center(
				_center.get()
			),
			sanguis::collision::radius(
				_radius.get()
			),
			_grid
		);
}
