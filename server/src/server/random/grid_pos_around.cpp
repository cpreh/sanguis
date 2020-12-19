#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/optional_pos.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/signed_pos.hpp>
#include <sanguis/server/random/grid_distance.hpp>
#include <sanguis/server/random/grid_pos.hpp>
#include <sanguis/server/random/grid_pos_around.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_signed_fun.hpp>
#include <fcppt/container/grid/clamped_min.hpp>
#include <fcppt/container/grid/clamped_sup_signed.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/fill.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::creator::optional_pos
sanguis::server::random::grid_pos_around(
	sanguis::random_generator &_random_generator,
	sanguis::creator::dim const &_size,
	sanguis::creator::pos const &_pos,
	sanguis::server::random::grid_distance const _distance
)
{
	auto const signed_pos(
		fcppt::math::vector::structure_cast<
			sanguis::creator::signed_pos,
			fcppt::cast::to_signed_fun
		>(
			_pos
		)
	);

	auto const signed_distance(
		fcppt::math::vector::fill<
			sanguis::creator::signed_pos
		>(
			fcppt::cast::to_signed(
				_distance.get()
			)
		)
	);

	return
		sanguis::server::random::grid_pos(
			_random_generator,
			fcppt::container::grid::clamped_min(
				signed_pos
				-
				signed_distance
			),
			fcppt::container::grid::clamped_sup_signed(
				signed_pos
				+
				signed_distance,
				_size
			)
		);
}
