#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_DAMAGE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_DAMAGE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/modifiers/random_increase.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/reference_impl.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace modifiers
{

struct damage
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
		_parameters.get().extra_damage(
			_parameters.get().damage().base()
			*
			sanguis::server::weapons::damage(
				sanguis::server::weapons::modifiers::random_increase(
					_random_generator,
					_difficulty
				)
				-
				fcppt::literal<
					sanguis::server::weapons::damage::value_type
				>(
					1
				)
			)
		);
	}
};

}
}
}
}

#endif
