#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <fcppt/literal.hpp>
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
					sanguis::creator::pos
				>(
					sanguis::creator::tile_size::value
					/
					fcppt::literal<
						sanguis::creator::size_type
					>(
						2u
					)
				)
			)
		);
}
