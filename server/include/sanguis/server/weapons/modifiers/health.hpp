#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_HEALTH_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/modifiers/random_increase.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis::server::weapons::modifiers
{

struct health
{
	template<
		typename Parameters
	>
	static
	void
	make(
		sanguis::random_generator &_random_generator, // NOLINT(google-runtime-references)
		sanguis::server::entities::enemies::difficulty const _difficulty,
		fcppt::reference<
			Parameters
		> const _parameters
	)
	{
		_parameters.get().extra_health(
			_parameters.get().health().base()
			*
			sanguis::server::health(
				sanguis::server::weapons::modifiers::random_increase(
					_random_generator,
					_difficulty
				)
			)
		);
	}
};

}

#endif
