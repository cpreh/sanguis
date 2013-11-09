#include <sanguis/random_generator.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/entities/enemies/factory/make_modifiers.hpp>
#include <sanguis/server/entities/enemies/modifiers/agile.hpp>
#include <sanguis/server/entities/enemies/modifiers/callback.hpp>
#include <sanguis/server/entities/enemies/modifiers/container.hpp>
#include <sanguis/server/entities/enemies/modifiers/fast.hpp>
#include <sanguis/server/entities/enemies/modifiers/health.hpp>
#include <fcppt/random/distribution/make_basic.hpp>
#include <fcppt/random/distribution/parameters/make_uniform_indices.hpp>


namespace
{

sanguis::server::entities::enemies::modifiers::container const callbacks{
	sanguis::server::entities::enemies::modifiers::callback{
		&sanguis::server::entities::enemies::modifiers::health
	},
	sanguis::server::entities::enemies::modifiers::callback{
		&sanguis::server::entities::enemies::modifiers::fast
	},
	sanguis::server::entities::enemies::modifiers::callback{
		&sanguis::server::entities::enemies::modifiers::agile
	}
};

}


sanguis::server::entities::enemies::modifiers::container
sanguis::server::entities::enemies::factory::make_modifiers(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty
)
{
	auto distribution(
		fcppt::random::distribution::make_basic(
			fcppt::random::distribution::parameters::make_uniform_indices(
				callbacks
			)
		)
	);

	// TODO: Choose multiple!
	return
		sanguis::server::entities::enemies::modifiers::container{
			callbacks[
				distribution(
					_random_generator
				)
			]
		};

}
