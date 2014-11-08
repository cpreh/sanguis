#include <sanguis/random_generator.hpp>
#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/server/random/grid_pos.hpp>
#include <fcppt/container/grid/size_type.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>


sanguis::creator::pos const
sanguis::server::random::grid_pos(
	sanguis::random_generator &_random_generator,
	sanguis::creator::pos const _pos,
	sanguis::creator::dim const _dim
)
{
	typedef
	fcppt::random::distribution::parameters::uniform_int<
		sanguis::creator::size_type
	>
	random_parameters;

	// TODO: Generalize this somewhere!

	auto const make_distribution(
		[
			_pos,
			_dim
		](
			fcppt::container::grid::size_type const _index
		)
		{
			return
				fcppt::random::distribution::make_basic(
					random_parameters(
						random_parameters::min(
							_pos[
								_index
							]
						),
						random_parameters::max(
							_dim[
								_index
							] - 1u
						)
					)
				);
		}
	);

	auto random_x(
		make_distribution(
			0
		)
	);

	auto random_y(
		make_distribution(
			1
		)
	);

	return
		sanguis::creator::pos{
			random_x(
				_random_generator
			),
			random_y(
				_random_generator
			)
		};
}
