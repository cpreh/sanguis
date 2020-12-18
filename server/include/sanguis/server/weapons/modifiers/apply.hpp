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
#include <sanguis/server/weapons/modifiers/guaranteed.hpp>
#include <sanguis/server/weapons/modifiers/potential.hpp>
#include <sanguis/server/weapons/modifiers/random_amount.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
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
Parameters
apply(
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::difficulty const _difficulty,
	sanguis::server::weapons::modifiers::guaranteed<
		Parameters
	> const &_guaranteed_modifiers,
	sanguis::server::weapons::modifiers::potential<
		Parameters
	> const &_potential_modifiers,
	Parameters &&_parameters
)
{
	using
	modifier_container
	=
	sanguis::server::weapons::modifiers::container<
		Parameters
	>;

	using
	callback
	=
	typename
	modifier_container::value_type;

	modifier_container const result(
		sanguis::server::random::draw<
			modifier_container
		>(
			_random_generator,
			_potential_modifiers.get(),
			sanguis::server::weapons::modifiers::random_amount(
				_random_generator,
				fcppt::strong_typedef_construct_cast<
					sanguis::server::random::amount,
					fcppt::cast::size_fun
				>(
					_potential_modifiers.get().size()
				)
			),
			sanguis::server::random::create_function<
				callback,
				callback
			>(
				fcppt::function<
					callback (
						callback const  &
					)
				>{
					[](
						callback const &_callback
					)
					{
						return
							_callback;
					}
				}
			),
			sanguis::server::random::less_function<
				callback
			>(
				fcppt::function<
					bool (
						callback const &,
						callback const &
					)
				>{
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
				}
			),
			sanguis::server::random::equal_function<
				callback
			>(
				fcppt::function<
					bool (
						callback const &,
						callback const &
					)
				>{
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
				}
			)
		)
	);

	for(
		auto const &modifier
		:
		_guaranteed_modifiers.get()
	)
		modifier(
			_random_generator,
			_difficulty,
			fcppt::make_ref(
				_parameters
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
		std::move(
			_parameters
		);
}

}
}
}
}

#endif
