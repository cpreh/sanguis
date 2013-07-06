#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/make_range.hpp>
#include <sanguis/collision/make_size.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/test.hpp>
#include <sanguis/creator/grid_crange.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/tile_is_solid.hpp>


bool
sanguis::collision::test(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius,
	sanguis::creator::grid const &_grid
)
{
	for(
		auto const &entry
		:
		sanguis::collision::make_range(
			_grid,
			_center,
			sanguis::collision::make_size(
				_radius
			)
		)
	)
		if(
			sanguis::creator::tile_is_solid(
				entry.value()
			)
		)
			return
				true;

	return
		false;
}
