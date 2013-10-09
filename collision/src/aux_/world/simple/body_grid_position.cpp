#include <sanguis/collision/aux_/world/simple/body.hpp>
#include <sanguis/collision/aux_/world/simple/body_grid_position.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/creator/tile_size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::creator::pos const
sanguis::collision::aux_::world::simple::body_grid_position(
	sanguis::collision::aux_::world::simple::body const &_body
)
{
	return
		fcppt::math::vector::structure_cast<
			sanguis::creator::pos
		>(
			fcppt::math::vector::structure_cast<
				sanguis::creator::signed_pos
			>(
				_body.center().get()
			)
			/
			fcppt::cast::to_signed(
				sanguis::creator::tile_size::value
			)
		);
}
