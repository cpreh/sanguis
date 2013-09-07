#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/aux/make_range.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/grid_crange.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/grid/clamp_signed_pos.hpp>
#include <fcppt/container/grid/make_pos_crange_start_end.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/ceil_div_signed.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::creator::grid_crange const
sanguis::collision::aux::make_range(
	sanguis::creator::grid const &_grid,
	sanguis::collision::center const _center,
	sanguis::collision::dim2 const _size
)
{
	sanguis::creator::difference_type const tile_size(
		fcppt::cast::to_signed(
			sanguis::creator::tile_size::value
		)
	);

	sanguis::collision::dim2 const half_size(
		_size
		/
		fcppt::literal<
			sanguis::collision::unit
		>(
			2
		)
	);

	sanguis::creator::pos const lower(
		fcppt::container::grid::clamp_signed_pos(
			fcppt::math::vector::structure_cast<
				sanguis::creator::signed_pos
			>(
				_center.get()
				-
				half_size
			)
			/
			tile_size,
			_grid.size()
		)
	);

	sanguis::creator::pos const upper(
		fcppt::container::grid::clamp_signed_pos(
			fcppt::math::vector::ceil_div_signed(
				fcppt::math::vector::structure_cast<
					sanguis::creator::signed_pos
				>(
					_center.get()
					+
					half_size
				),
				tile_size
			),
			_grid.size()
		)
	);

	return
		fcppt::container::grid::make_pos_crange_start_end(
			_grid,
			lower,
			upper
		);
}
