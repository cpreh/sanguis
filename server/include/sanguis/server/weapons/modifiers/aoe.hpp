#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_AOE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_AOE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/aoe.hpp>
#include <sanguis/server/weapons/modifiers/random_increase.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


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
aoe(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	fcppt::reference_wrapper<
		Parameters
	> const _parameters
)
{
	_parameters.get().extra_aoe(
		_parameters.get().aoe().base()
		*
		sanguis::server::weapons::aoe(
			std::min(
				sanguis::server::weapons::modifiers::random_increase(
					_random_generator,
					_difficulty
				),
				_parameters.get().aoe().base().get()
				*
				5.f
			)
			-
			fcppt::literal<
				sanguis::server::weapons::aoe::value_type
			>(
				1
			)
		)
	);
}

}
}
}
}

#endif
