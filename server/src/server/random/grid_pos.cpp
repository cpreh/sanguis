#include <sanguis/random_generator.hpp>
#include <sanguis/creator/min.hpp>
#include <sanguis/creator/optional_pos.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/size_type.hpp>
#include <sanguis/creator/sup.hpp>
#include <sanguis/server/random/grid_pos.hpp>
#include <fcppt/use.hpp>
#include <fcppt/container/grid/min_less_sup.hpp>
#include <fcppt/container/grid/size_type.hpp>
#include <fcppt/math/static_size.hpp>
#include <fcppt/math/vector/at_c.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>


sanguis::creator::optional_pos
sanguis::server::random::grid_pos(
	sanguis::random_generator &_random_generator,
	sanguis::creator::min const _min,
	sanguis::creator::sup const _sup
)
{
	if(
		!fcppt::container::grid::min_less_sup(
			_min,
			_sup
		)
	)
		return
			sanguis::creator::optional_pos();

	typedef
	fcppt::random::distribution::parameters::uniform_int<
		sanguis::creator::size_type
	>
	random_parameters;

	// TODO: Generalize this somewhere!

	auto const make_distribution(
		[
			_min,
			_sup
		](
			auto const _index
		)
		{
			FCPPT_USE(
				_index
			);

			typedef
			decltype(
				_index
			)
			index;

			return
				fcppt::random::distribution::make_basic(
					random_parameters(
						random_parameters::min(
							fcppt::math::vector::at_c<
								index::value
							>(
								_min.get()
							)
						),
						random_parameters::max(
							fcppt::math::vector::at_c<
								index::value
							>(
								_sup.get()
							)
							-
							1u
						)
					)
				);
		}
	);

	auto random_x(
		make_distribution(
			fcppt::math::static_size<
				0
			>{}
		)
	);

	auto random_y(
		make_distribution(
			fcppt::math::static_size<
				1
			>{}
		)
	);

	return
		sanguis::creator::optional_pos{
			sanguis::creator::pos{
				random_x(
					_random_generator
				),
				random_y(
					_random_generator
				)
			}
		};
}
