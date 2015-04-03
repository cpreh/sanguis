#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/test.hpp>
#include <sanguis/collision/impl/make_range.hpp>
#include <sanguis/creator/grid_crange.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/tile_is_solid.hpp>


bool
sanguis::collision::test(
	sanguis::collision::center const _center,
	sanguis::collision::dim2 const _size,
	sanguis::creator::grid const &_grid
)
{
	for(
		auto const &entry
		:
		sanguis::collision::impl::make_range(
			_grid,
			_center,
			_size
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
