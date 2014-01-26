#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_HEALTH_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_HEALTH_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/modifiers/random_increase.hpp>
#include <fcppt/reference_wrapper_impl.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace modifiers
{

template<
	typename Parameters
>
void
health(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	fcppt::reference_wrapper<
		Parameters
	> const _parameters
)
{
	_parameters.get().health(
		_parameters.get().health()
		*
		sanguis::server::health(
			sanguis::server::weapons::modifiers::random_increase(
				_random_generator,
				_difficulty
			)
		)
	);
}

}
}
}
}

#endif