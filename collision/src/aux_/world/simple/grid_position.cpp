#include <sanguis/collision/center.hpp>
#include <sanguis/collision/aux_/world/simple/grid_position.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/cast/float_to_int_fun.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::creator::pos const
sanguis::collision::aux_::world::simple::grid_position(
	sanguis::collision::center const _center
)
{
	return
		fcppt::math::vector::structure_cast<
			sanguis::creator::pos,
			fcppt::cast::float_to_int_fun
		>(
			fcppt::math::vector::structure_cast<
				sanguis::creator::signed_pos,
				fcppt::cast::int_to_float_fun
			>(
				_center.get()
			)
			/
			fcppt::cast::to_signed(
				sanguis::creator::tile_size::value
			)
		);
}
