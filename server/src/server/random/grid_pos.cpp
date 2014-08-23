#include <sanguis/random_generator.hpp>
#include <sanguis/creator/dim.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/server/random/grid_pos.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>


sanguis::creator::pos const
sanguis::server::random::grid_pos(
	sanguis::random_generator &_random_generator,
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
		[](
			sanguis::creator::size_type const _size
		)
		{
			return
				fcppt::random::distribution::make_basic(
					random_parameters(
						random_parameters::min(
							0u
						),
						random_parameters::max(
							_size - 1u
						)
					)
				);
		}
	);

	auto random_x(
		make_distribution(
			_dim.w()
		)
	);

	auto random_y(
		make_distribution(
			_dim.h()
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
