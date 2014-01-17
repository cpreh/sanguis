#ifndef SANGUIS_SERVER_WEAPONS_MODIFIERS_APPLY_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_MODIFIERS_APPLY_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/random/amount.hpp>
#include <sanguis/server/random/create_function.hpp>
#include <sanguis/server/random/draw.hpp>
#include <sanguis/server/random/equal_function.hpp>
#include <sanguis/server/random/less_function.hpp>
#include <sanguis/server/weapons/modifiers/container.hpp>
#include <sanguis/server/weapons/modifiers/random_amount.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>


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
Parameters
apply(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	sanguis::server::weapons::modifiers::container<
		Parameters
	> const &_potential_modifiers,
	Parameters _parameters
)
{
	typedef
	sanguis::server::weapons::modifiers::container<
		Parameters
	>
	modifier_container;

	typedef
	typename
	modifier_container::value_type
	callback;

	modifier_container const result(
		sanguis::server::random::draw<
			modifier_container
		>(
			_random_generator,
			_potential_modifiers,
			sanguis::server::weapons::modifiers::random_amount(
				_random_generator,
				fcppt::strong_typedef_construct_cast<
					sanguis::server::random::amount
				>(
					_potential_modifiers.size()
				)
			),
			sanguis::server::random::create_function<
				callback,
				callback
			>(
				[](
					callback const &_callback
				)
				{
					return
						_callback;
				}
			),
			sanguis::server::random::less_function<
				callback
			>(
				[](
					callback const &_callback1,
					callback const &_callback2
				)
				{
					return
						std::less<
							callback
						>()(
							_callback1,
							_callback2
						);
				}
			),
			sanguis::server::random::equal_function<
				callback
			>(
				[](
					callback const &_callback1,
					callback const &_callback2
				)
				{
					return
						_callback1
						==
						_callback2;
				}
			)
		)
	);

	for(
		auto const &modifier
		:
		result
	)
		modifier(
			_random_generator,
			_difficulty,
			fcppt::make_ref(
				_parameters
			)
		);

	return
		_parameters;
}

}
}
}
}

#endif
