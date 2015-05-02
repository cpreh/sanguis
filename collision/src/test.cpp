#include <sanguis/collision/center.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/test.hpp>
#include <sanguis/collision/impl/make_range.hpp>
#include <sanguis/creator/grid_crange.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <fcppt/algorithm/contains_if.hpp>
#include <fcppt/container/grid/pos_reference_impl.hpp>


bool
sanguis::collision::test(
	sanguis::collision::center const _center,
	sanguis::collision::radius const _radius,
	sanguis::creator::grid const &_grid
)
{
	return
		fcppt::algorithm::contains_if(
			sanguis::collision::impl::make_range(
				_grid,
				_center,
				_radius
			),
			[](
				fcppt::container::grid::pos_reference<
					sanguis::creator::grid const
				> const _entry
			)
			{
				return
					sanguis::creator::tile_is_solid(
						_entry.value()
					);
			}
		);
}
