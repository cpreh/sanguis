#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_MAGAZINE_SIZE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_MAGAZINE_SIZE_HPP_INCLUDED

#include <sanguis/magazine_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/modifiers/random_increase.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cmath>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace modifiers
{

struct magazine_size
{
	template<
		typename Parameters
	>
	static
	void
	make(
		sanguis::random_generator &_random_generator,
		sanguis::server::entities::enemies::difficulty const _difficulty,
		fcppt::reference<
			Parameters
		> const _parameters
	)
	{
		_parameters.get().extra_magazine_size(
			// TODO: What to use here?
			sanguis::server::weapons::magazine_size(
				std::min(
					fcppt::cast::to_unsigned(
						fcppt::cast::float_to_int<
							std::make_signed<
								sanguis::magazine_type
							>::type
						>(
							std::sqrt(
								std::sqrt(
									sanguis::server::weapons::modifiers::random_increase(
										_random_generator,
										_difficulty
									)
								)
							)
						)
					),
					_parameters.get().magazine_size().value().get()
					*
					fcppt::literal<
						sanguis::magazine_type
					>(
						2
					)
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
