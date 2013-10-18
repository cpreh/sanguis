#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/aux_/make_spiral_range.hpp>
#include <sanguis/creator/difference_type.hpp>
#include <sanguis/creator/grid_spiral_range.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/container/grid/make_spiral_range.hpp>
#include <fcppt/math/ceil_div_signed.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::creator::grid_spiral_range const
sanguis::collision::aux_::make_spiral_range(
	sanguis::collision::center const _center,
	sanguis::collision::dim2 const _size
)
{
	sanguis::creator::difference_type const tile_size(
		fcppt::cast::to_signed(
			sanguis::creator::tile_size::value
		)
	);

	return
		fcppt::container::grid::make_spiral_range(
			fcppt::math::vector::structure_cast<
				sanguis::creator::signed_pos
			>(
				_center.get()
			)
			/
			tile_size,
			fcppt::math::ceil_div_signed(
				fcppt::cast::float_to_int<
					sanguis::creator::difference_type
				>(
					std::max(
						_size.w(),
						_size.h()
					)
				),
				tile_size
			)
		);
}
