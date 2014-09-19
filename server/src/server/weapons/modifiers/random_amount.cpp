#include <sanguis/random_generator.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/weapons/modifiers/random_amount.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/distribution/transform/strong_typedef.hpp>


sanguis::server::random::amount const
sanguis::server::weapons::modifiers::random_amount(
	sanguis::random_generator &_random_generator,
	sanguis::server::random::amount const _max
)
{
	// TODO: Different distribution?
	typedef
	fcppt::random::distribution::parameters::uniform_int<
		sanguis::server::random::amount
	>
	parameters;

	auto distribution(
		fcppt::random::distribution::make_basic(
			parameters(
				parameters::min(
					sanguis::server::random::amount(
						0u
					)
				),
				parameters::max(
					_max
				)
			)
		)
	);

	return
		distribution(
			_random_generator
		);
}
