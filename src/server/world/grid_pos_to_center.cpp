#include <sanguis/pixels_per_meter.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::server::center const
sanguis::server::world::grid_pos_to_center(
	sanguis::creator::pos const _pos
)
{
	return
		sanguis::server::center(
			fcppt::math::vector::structure_cast<
				sanguis::server::vector
			>(
				_pos
				*
				sanguis::creator::tile_size::value
				+
				fcppt::math::vector::fill<
					sanguis::creator::pos::dim_wrapper::value
				>(
					static_cast<
						sanguis::creator::size_type
					>(
						sanguis::creator::tile_size::value
						/
						2u
					)
				)
			)
			/
			static_cast<
				sanguis::server::space_unit
			>(
				sanguis::pixels_per_meter()
			)
		);
}
