#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/server/random/grid_distance.hpp>
#include <sanguis/server/random/grid_pos.hpp>
#include <sanguis/server/random/grid_pos_around.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/container/grid/clamp_pos.hpp>
#include <fcppt/container/grid/clamp_signed_pos.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/to_dim.hpp>


sanguis::creator::pos const
sanguis::server::random::grid_pos_around(
	sanguis::random_generator &_random_generator,
	sanguis::creator::dim const _size,
	sanguis::creator::pos const _pos,
	sanguis::server::random::grid_distance const _distance
)
{
	return
		sanguis::server::random::grid_pos(
			_random_generator,
			fcppt::container::grid::clamp_signed_pos(
				fcppt::math::vector::structure_cast<
					sanguis::creator::signed_pos,
					fcppt::cast::to_signed_fun
				>(
					_pos
				)
				-
				fcppt::cast::to_signed(
					_distance.get()
				),
				_size
			),
			fcppt::math::vector::to_dim(
				fcppt::container::grid::clamp_pos(
					_pos
					+
					_distance.get(),
					_size
				)
			)
		);
}
